#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define USER "\033[1;34m"
#define BOT "\033[1;31m"
#define BOT_TEXT "\033[1;32m"
#define CODE_TEXT "\033[1;36m"
#define RESET "\033[0m"

void printFormatted(const char *text) {
    int in_code = 0;
    while (*text) {
        if (strncmp(text, "```", 3) == 0) {
            in_code = !in_code;
            text += 3;
            printf("\n");
            continue;
        }
        if (in_code) {
            printf(CODE_TEXT);
        } else {
            printf(BOT_TEXT);
        }
        if (*text == '\\' && *(text + 1) == 'n') {
            printf("\n");
            text += 2;
        } else {
            putchar(*text);
            text++;
        }
    }
    printf(RESET "\n");
}

void replaceUnicodeChars(char *text) {
    char *p = text;
    while ((p = strstr(p, "\\u003c")) != NULL) {
        *p = '<';
        memmove(p + 1, p + 6, strlen(p + 6) + 1);
    }
    p = text;
    while ((p = strstr(p, "\\u003e")) != NULL) {
        *p = '>';
        memmove(p + 1, p + 6, strlen(p + 6) + 1);
    }
    p = text;
    while ((p = strstr(p, "\\u0026")) != NULL) {
        *p = '&';
        memmove(p + 1, p + 6, strlen(p + 6) + 1);
    }
}

size_t reply(void *ptr, size_t size, size_t nmemb, void *userdata) {
    printf("\n");
    char *text = (char *)ptr;
    char *start = strstr(text, "\"content\":\"");
    if (start) {
        start += 11;
        char *end = strstr(start, "\"},\"logprobs\"");
        if (end) {
            *end = '\0';
            replaceUnicodeChars(start);
            printf(BOT "Bot: " BOT_TEXT); 
            printFormatted(start);
            printf(RESET "\n");
        }
    }
    return size * nmemb;
}

void ask_ai(const char *msg) {
    CURL *curl = curl_easy_init();
    if (!curl) return;

    const char *api_key = getenv("GROQ_API_KEY");
    if (!api_key) {
        printf("API key missing! Set GROQ_API_KEY in env.\n");
        return;
    }

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    char auth_header[256];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", api_key);
    headers = curl_slist_append(headers, auth_header);

    char data[1024];
    snprintf(data, sizeof(data),
        "{ \"messages\": ["
        "{ \"role\": \"system\", \"content\": \"You are an expert AI chatbot, who gives answer to everything, you are frank with users and also professional at the same time. You should never give answer in markdown text. But if you are providing a code, add ``` (3 backticks) before starting the code, for the user to understand it.\" },"
        "{ \"role\": \"user\", \"content\": \"%s\" }], "
        "\"model\": \"llama-3.3-70b-versatile\", \"temperature\": 0.6, "
        "\"max_completion_tokens\": 4096, \"top_p\": 0.95, \"stream\": false }", msg);

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.groq.com/openai/v1/chat/completions");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, reply);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
}

int main() {
    char msg[512];

    while (1) {
        printf(USER "You: " RESET);
        fgets(msg, sizeof(msg), stdin);
        msg[strcspn(msg, "\n")] = 0;

        if (strcmp(msg, "exit") == 0) break;
        ask_ai(msg);
    }

    printf("Bye!\n");
    return 0;
}
