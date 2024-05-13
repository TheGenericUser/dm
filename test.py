from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.wait import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.keys import Keys
from selenium.common.exceptions import NoSuchElementException, StaleElementReferenceException
import time, random, pyperclip


option = webdriver.ChromeOptions()
option.add_experimental_option("debuggerAddress", "localhost:9222")
driver = webdriver.Chrome(options=option)
wait = WebDriverWait(driver, 10)
chunk_size = 50

def read_and_split_file(file_path, chunk_size):
    with open(file_path, 'r', encoding='utf-8') as file:
        # Read all lines from the file
        lines = file.readlines()

        # Calculate the number of lines in the file
        total_lines = len(lines)

        # Calculate the number of chunks based on the specified size
        num_chunks = -(-total_lines // chunk_size)  # Ceiling division

        # Split the lines into chunks
        chunks = [lines[i * chunk_size:(i + 1) * chunk_size] for i in range(num_chunks)]

    return chunks



driver.get('https://chat.openai.com/')
time.sleep(5)
path_for_translate = ''
path_to_translated = ''
input_area = wait.until(EC.presence_of_element_located((By.XPATH, '//textarea[@id = "prompt-textarea"]'))).find_element(By.XPATH, '//textarea[@id = "prompt-textarea"]')
text_box_number = 0
alert_text_box_number = 0
for i in range(669, 775+1):
    text_output =''
    input_path = path_for_translate + f'{i}.txt'
    output_path = path_to_translated + f'{i}.txt'
    file_chunks = read_and_split_file(input_path, 50)
    for chunk in file_chunks:
        text_to_send = "translate to english:" +'\n' +'\n'.join(chunk)
        pyperclip.copy(text_to_send)
        input_area.send_keys(Keys.CONTROL + 'v')
        time.sleep(random.uniform(0.1, 0.5))
        input_area.send_keys(Keys.ENTER)
        typing = True
        time.sleep(10)
        while typing:
            try:
                just_before_del = driver.find_element(By.XPATH, "//div[@class='result-streaming markdown prose w-full break-words dark:prose-invert dark']")
                test = just_before_del.text
            except (NoSuchElementException, StaleElementReferenceException):
                text_box_number += 1
                time.sleep(random.uniform(1, 3))
                all_return = 0
                try:                   
                    all_return = driver.find_elements(By.XPATH, "//div[@class='markdown prose w-full break-words dark:prose-invert dark']") 
                    # returns the okay boxes throughout the page.
                    if len(all_return) == text_box_number:
                        output = all_return[-1].text
                        typing = False
                    else:
                        text_box_number -= 1
                        raise NoSuchElementException
                except NoSuchElementException:
                    try:
                        all_return_alert = driver.find_elements(By.XPATH, "//div[@class='text-token-text-tertiary markdown prose w-full break-words dark:prose-invert dark']")
                        alert_text_box_number += 1
                        if alert_text_box_number == len(all_return_alert):
                            output = all_return_alert[-1].text
                            typing = False
                        else:
                            alert_text_box_number -= 1
                            raise NoSuchElementException
                    except NoSuchElementException:
                        try:
                            selection_choice = driver.find_elements(By.XPATH, "//button[@class='relative flex w-full flex-col gap-1 bg-white cursor-pointer truncate rounded-lg border border-gray-300 text-left dark:bg-gray-700 py-4 px-5 hover:border-[var(--avatar-color)]']")
                            time.sleep(5)
                            if(len(selection_choice) == 0):
                                raise NoSuchElementException
                            elif len(selection_choice) > 0:
                                selection_choice[0].click()
                                text_box_number += 1
                            else: 
                                output = just_before_del.text
                                raise NoSuchElementException
                        except NoSuchElementException: typing = False
        text_output += output + '\n'
        text_output = '\n\n'.join(line.strip() for line in text_output.splitlines() if line.strip())
    with open(output_path, 'w', encoding="utf-8") as file:
        file.write(text_output)
