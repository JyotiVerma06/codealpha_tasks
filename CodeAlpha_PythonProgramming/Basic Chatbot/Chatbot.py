def chatbot_response(user_input):
    # Convert input to lowercase for easy matching
    user_input = user_input.lower()

    if "hello" in user_input or "hi" in user_input:
        return "Hi there!"
    elif user_input == "how are you":
        return "I'm fine, thanks!"
    elif "what is your name" in user_input:
        return "I'm your friendly chatbot!"
    elif "thank you" in user_input or "thanks" in user_input:
        return "You're welcome!"
    elif "good morning" in user_input:
        return "Good morning! Hope you have a great day."
    elif "good night" in user_input:
        return "Good night! Sweet dreams."
    elif "what can you do" in user_input:
        return "I can chat with you, answer simple questions, and keep you company."
    elif "Are you mad" in user_input:
        return "Just like you."
    elif "where are you from" in user_input:
        return "I live inside your computer program."
    elif "tell me a joke" in user_input:
        return "Why don’t programmers like nature? Too many bugs!"
    elif "who made you" in user_input:
        return "I was created by a programmer Jyoti Verma"
    elif "time" in user_input:
        import datetime
        return f"The current time is {datetime.datetime.now().strftime('%H:%M')}"
    elif "date" in user_input:
        import datetime
        return f"Today's date is {datetime.datetime.now().strftime('%Y-%m-%d')}"
    elif user_input == "bye":
        return "Goodbye!"
    else:
        return "Sorry, I don't understand that."


# Main loop
print("Chatbot is ready! Type 'bye' to exit.")
while True:
    user_message = input("You: ")
    reply = chatbot_response(user_message)
    print("Bot:", reply)

    if user_message.lower() == "bye":
        break