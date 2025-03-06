# 🧠 AI Chatbot in C using Groq API  

🚀 **A lightweight and efficient AI chatbot built in C**, leveraging **cURL** to interact with the **Groq API** for AI-generated responses. This project explores AI development in a low-level programming environment, integrating real-time conversation capabilities into a **terminal-based chatbot**.

## 📌 Features

✅ **Groq API Integration** – Fetches AI-generated responses dynamically  
✅ **cURL for HTTP Requests** – Handles API communication seamlessly  
✅ **Interactive Chat Interface** – Smooth user experience in the terminal  
✅ **Optimized String Processing** – Efficient parsing and formatting of AI responses  
✅ **Lightweight & Fast** – Built entirely in C for performance

## 🛠️ Installation & Usage  

### 1️⃣ Prerequisites

Ensure you have the following installed:  

- **GCC Compiler** (`gcc`)
- **Groq API Key** (Sign up at [Groq API](https://groq.com/) and set `GROQ_API_KEY` in your environment)
- **cURL Library** (`libcurl`)  

To install `libcurl`:  

```sh
# Ubuntu/Debian
sudo apt update && sudo apt install libcurl4-openssl-dev

# Fedora
sudo dnf install libcurl-devel

# Arch Linux
sudo pacman -S curl

# macOS (Homebrew)
brew install curl
```

For Windows:

1. Download libcurl from [https://curl.se/windows/](curl.se/windows).
2. Extract and add the include and lib paths to your MinGW compiler.

![alt text](<image.jpg>)

### 2️⃣ Clone the Repository

```sh
git https://github.com/subhadeeproy3902/AI-Terminal-Bot.git
cd AI-Terminal-Bot
```

### 3️⃣ Set Up API Key

```sh
export GROQ_API_KEY="your_api_key_here"
```

For Windows (PowerShell):

```powershell
$env:GROQ_API_KEY="your_api_key_here"
```

### 4️⃣ Compile the Chatbot

```sh
gcc chatbot.c -o c.out -lcurl
```

### 5️⃣ Run the Chatbot

```sh
./c.out
```

Start chatting! Type `exit` to quit.

## 🔥 How It Works  

1. **User Input**: The user types a message in the terminal.  
2. **API Request**: The chatbot sends the message to the **Groq API** using `cURL`.  
3. **AI Response**: The API processes the request and returns a response.  
4. **Display**: The chatbot extracts the response and prints it in a formatted way.  

💡 **The bot is designed to be direct, professional, and does not use markdown in responses.**  

## 📜 License  

This project is open-source under the **MIT License**. Feel free to use, modify, and distribute it as needed.  

---

If you like this project, consider giving it a ⭐ on GitHub!  

---

🚀 **Explore AI development beyond web apps! Build intelligent CLI tools in C!** 🔥  
