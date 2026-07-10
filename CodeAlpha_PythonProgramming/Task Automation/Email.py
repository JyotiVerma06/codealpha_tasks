import re


input_file = r"C:\PROJECTS\CodeAlpha_PythonProgramming\Task Automation\emails.txt"


output_file = r"C:\PROJECTS\CodeAlpha_PythonProgramming\Task Automation\extracted_emails.txt"


with open(input_file, "r", encoding="utf-8") as f:
    text = f.read()


pattern = r"[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}"


emails = re.findall(pattern, text)


with open(output_file, "w", encoding="utf-8") as f:
    for email in emails:
        f.write(email + "\n")

print("Emails extracted and saved to extracted_emails.txt")
