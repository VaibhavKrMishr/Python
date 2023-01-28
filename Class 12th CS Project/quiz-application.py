try:
	import requests
except ImportError:
	raise ImportError("Please Install the 'requests' package and try again")
	
from random import shuffle
from html import unescape
from time import sleep

print("Welcome to our Quiz Program") #Welcome
print("It will ask you your preferences for the questions and then the quiz will start")
print("There is no time limit")
print()

categories = {"General Knowlegde": 9,
					"Entertainment: Books": 10,
					"Entertainment: Film": 11,
					"Entertainemnet: Music": 12,
					"Entertainement: Television": 14,
					"Entertainment: Video Games": 15,
					"Entertainement: Board Games": 16,
					"Science and Nature": 17,
					"Science: Computers": 18,
					"Science: Mathematics": 19,
					"Mythology": 20,
					"Sports": 21,
					"Geography": 22,
					"History": 23,
					"Politics": 24,
					"Art": 25,
					"Celebrities": 26,
					"Animals": 27,
					"Vehicals": 28,
					"Entertainement: Comics": 29,
					"Science: Gadgets": 30,
					"Entertainment: Japanese Anime and Manga": 31,
					"Entertainment: Cartoon and Animations": 32,
					}
					
difficulties = {"Easy": "easy", "Medium": "medium", "Hard": "hard"}
diff_rev = {v: k for k, v in difficulties.items()}
types = {"Multiple Choice": "multiple", "True/False": "boolean"}
types_rev = {v: k for k, v in types.items()}

amount = input("How many questions do you want? (max 50, press enter to accept the default value of 10): ")
if amount.isnumeric():
	if int(amount) > 50 or int(amount) < 1:
		raise ValueError("Minimum 1 and Maximum 50 questions")
	else:
		amount = int(amount)
elif not amount:
	amount = 10
else:
	raise ValueError(f"Required a number > 0 and < 50, got {amount}")
	
# print(amount, type(amount))
print("Please Choose a category:")
for _ in categories:
	print(f"\t{_} ({categories[_]})")
	
cat = input("\nEnter the desired category id (or press enter the choose all): ")
if cat.isnumeric():
	if int(cat) not in categories.values():
		raise ValueError("Kindly check the id you entered")
	else:
		cat = int(cat)
elif not cat:
	cat = None
else:
	raise ValueError(f"Required an id, got {cat}")
	
# print(cat)
diff = input("Choose a Difficulty\n1. Easy\n2. Medium\n3. Hard\n(Enter number or press enter for all): ")
if diff.isnumeric():
	if diff not in tuple("123"):
		raise ValueError("Required one of 1, 2, or 3")
	else:
		diff = list(difficulties.values())[int(diff)-1]
elif not diff: diff = None
else:
	raise ValueError(f"Required a number, got {diff}")

print("Choose a question Type")
tp = input("1. Multiple Choice\n2. True/False\n(enter number or press enter for both): ")
if tp.isnumeric():
	if tp not in tuple("12"):
		raise ValueError("Required one of 1 and 2")
	else:
		tp = list(types.values())[int(tp)-1]
elif not tp: tp = None
else:
	raise ValueError(f"Required a number, got {tp}")


# print(amount, cat, diff, tp)

url = f"https://opentdb.com/api.php?amount={amount}"
if cat:
	url += f"&category={cat}"

if diff:
	url += f"&difficulty={diff}"
	
if tp:
	url += f"&type={tp}"
	
#url = f"https://opentdb.com/api.php?amount={amount}&category={cat}&difficulty={diff}&type={tp}"

# print(url)
print("Contacting API...")
response = requests.get(url)
# print(response.json())

print()

data = response.json()

if data['response_code'] != 0:
	print("API Error")
	exit()
	
points = 0
	
for i, r in enumerate(data['results'], 1):
	print(f"[{r['category']}, Difficulty {diff_rev[r['difficulty']]}, {types_rev[r['type']]}]")
	print(f"Q{i}. {unescape(r['question'])}")
	
	opts = [r['correct_answer'], *r['incorrect_answers']]
	shuffle(opts)
	for j, o in enumerate(opts, 1):
		print(f"{j}. {unescape(o)}")
		
	opt = input("Choose the correct option: ")
	if opt.isnumeric():
		if int(opt) in range(1, len(opts)+1):
			if opts[int(opt)-1] == r['correct_answer']:
				print("Wow! Correct Answer\n")
				points += 1
				if r['difficulty'] == 'easy': points += 0
				elif r['difficulty'] == 'medium': points += 1
				elif r['difficulty'] == 'hard': points += 2
				sleep(1)
				continue
	
	print("Oh no! Wrong Answer")
	print(f"Correct Answer is: \'{unescape(r['correct_answer'])}\'")
	
	print()
	sleep(2)
	
print(f"You got {points} points for {amount} questions!")
print(f"You Universal score is {round(points/amount * 100, 2)}")
print()
