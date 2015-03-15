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

#Main Runtime
#dirName = os.system('pwd')
dirName = os.getcwd()
matricies = DoubleList()

for file in os.listdir(dirName):
	if file.endswith(".csv"):
		with open(file, 'r') as csvfile:
			matrix1 = csv.reader(csvfile, delimiter=',', quotechar='|')
			print (seperator + "\n~~~~~~~~~~New Matrix from file: " + str(file) + "~~~~~~~~~~");
			
			#initialize a new stack
			column = stack()

			rows = 0			
			#Stack up rows from file, fow valid calculation
			for row in matrix1:
				#Push each 
				rows += 1
				column.push(len(row))
				print ("\t"+str(row))

			#Calculate matrix or not
			x = column.peek()
			if column.count(x) != len(column):
				print ("\n\tNot a Matrix - Non Square:")
			else:
				print ("\n\tMatrix Confirmed:")
				if rows == len(column):
					matricies.append(file, True, rows, len(column))
				else:
					matricies.append(file, False, rows, len(column))	

			print "\t\t|rows| = " + str(rows)
			print ("\t\tEntries in Column Stack or |column| = " + str(len(column)))
			print ("\t\tColumn Stack = " + str(column))
			num_rows = len(row)
			print (seperator)

matricies.show()