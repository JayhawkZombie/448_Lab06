import csv
import os

seperator = "~"*53

#declare stack object based on list class
class stack(list):
	def peek(self):
		return self[0]
	def push(self, item):
		self.append(item)
	def isEmpty(self):
		return not self

class Node(object):

	def __init__(self, data, prev, next, square, n, m):
		self.data = data
		self.square = square
		self.n = n
		self.m = m
		self.prev = prev
		self.next = next

class DoubleList(object):
 
	head = None
	tail = None
 
	def append(self, data, square, n, m):
		new_node = Node(data, None, None, square, n, m)
		if self.head is None:
			self.head = self.tail = new_node
		else:
			new_node.prev = self.tail
			new_node.next = None
			self.tail.next = new_node
			self.tail = new_node

	def remove(self, node_value):
		current_node = self.head
 
		while current_node is not None:
			if current_node.data == node_value:
				# if it's not the first element
				if current_node.prev is not None:
					current_node.prev.next = current_node.next
					current_node.next.prev = current_node.prev
				else:
					# otherwise we have no prev (it's None), head is the next one, and prev becomes None
					self.head = current_node.next
					current_node.next.prev = None
 
			current_node = current_node.next
 
	def show(self):
		print "Show list data:"
		current_node = self.head
		while current_node is not None:
			print current_node.prev.data if hasattr(current_node.prev, "data") else None,
			print current_node.data,
			print current_node.next.data if hasattr(current_node.next, "data") else None
 
			current_node = current_node.next
		print "~"*53


def getMat(mat):
	dirName = os.getcwd()

	for file in os.listdir(dirName):
		if file.endswith(".csv"):
			with open(file, 'r') as csvfile:
				matrix1 = csv.reader(csvfile, delimiter=',', quotechar='|')
				print ("~~~~~~~~~~New Matrix from file: " + str(file) + "~~~~~~~~~~");
				
				#initialize a new stack to store the Value of each column 
				columnStack = stack()

				rows = 0			
				#Stack up rows from file, for valid calculation
				for row in matrix1:
					#Push each 
					rows += 1
					columnStack.push(len(row))
					print ("\t"+str(row))

				#Compare the first value to the rest of the columnStack values
				x = columnStack.peek()
				if columnStack.count(x) != len(columnStack):
					print ("\n\tNot a Matrix - Non Square:")
				else:
					print ("\n\tMatrix Confirmed:")
					if rows == len(columnStack):
						mat.append(file, True, rows, len(columnStack))
					else:
						mat.append(file, False, rows, len(columnStack))   

				print "\t\t|rows| = " + str(rows)
				print ("\t\tEntries in Column Stack or |column| = " + str(len(columnStack)))
				print ("\t\tColumn Stack = " + str(columnStack))
				num_rows = len(row)
				print (seperator)
	#return mat

#Main Runtime
def main():
	mat = DoubleList()
	getMat(mat)

	exit_flag = 1
	while exit_flag > 0:
		print "Refresh From File ---- 1\nDisplay Matrix listings ---- 2\nExit ---- 3"
		prompt = int(input(":"))

		if prompt < 0 or prompt > 3:
			print "invalid input - please try again"
		elif prompt == 1:
			getMat(mat)
		elif prompt == 2:
			mat.show()
		else:
			exit_flag = 0
			print "Program Ending..."
	#mat.show()

main()