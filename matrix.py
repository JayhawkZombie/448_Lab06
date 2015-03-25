import csv
import os
import pprint

seperator = "~"*53

class Matrix(object):

	def __init__(self, array, filename, prev, nnext, square, n, m):
		self.square = square
		self.filename = filename
		self.array = array
		self.n = n
		self.m = m
		self.prev = prev
		self.next = nnext

	def show(self):
		for x in range(0,self.n):
			print self.array[x]

class MatrixList(object):
 
	head = None
	tail = None
 
	def append(self, array, filename, square, n, m):
		new_matrix = Matrix(array, filename, None, None, square, n, m)
		if self.head is None:
			self.head = self.tail = new_matrix
		else:
			new_matrix.prev = self.tail
			new_matrix.next = None
			self.tail.next = new_matrix
			self.tail = new_matrix

	def remove(self, matrix_value):
		current_matrix = self.head
 
		while current_matrix is not None:
			if current_matrix.array == matrix_value:
				# if it's not the first element
				if current_matrix.prev is not None:
					current_matrix.prev.next = current_matrix.next
					current_matrix.next.prev = current_matrix.prev
				else:
					# otherwise we have no prev (it's None), head is the next one, and prev becomes None
					self.head = current_matrix.next
					current_matrix.next.prev = None
 
			current_matrix = current_matrix.next
 
	def show(self):
		print "\n" + seperator + "\nMatrixList.show()"
		current_matrix = self.head

		while current_matrix is not None:
			print "\nMatrix Filename: " + current_matrix.filename
			print "Matrix array:\n"
			current_matrix.show()
			print "Rows: " + str(current_matrix.n)
			print "Col: " + str(current_matrix.m)
			print "Square: " + str(current_matrix.square)
			current_matrix = current_matrix.next
		print "~"*53

	def listEntries(self):
		i = 1
		current_matrix = self.head
		while current_matrix is not None:
			print str(i) + ": " + current_matrix.filename
			i+=1
			current_matrix = current_matrix.next
		return i-1

#global declarations for scripting simplicity
dirName = os.getcwd()

def refresh():
	matricies = MatrixList()
	print "\nReading matricies from: " + dirName
	for file in os.listdir(dirName):
		if file.endswith(".csv"):
			csvfile = open(file, 'rb')
			array = []

			for line in csvfile:
				#Parse the csvfile and seperate number on ',' characters
				l = [g.strip() for g in line.split(',')]
				#Push the seperated string over numbers onto an array
				array.append(l)

			columnStack = list()
			for x in range(0,len(array)):
				columnStack.append(len(array[x]))
				#for y in range(0, len(array[x])):
					#print "Array[" + str(x) + "," + str(y) + "]: " + str(array[x][y])

			if columnStack.count(columnStack[0]) != len(columnStack):
					print ("Not a Matrix - Columns are inconsistent\n")
			else:
				print "Matrix Confirmed:" + file
				if len(array) == len(array[0]):
					matricies.append(array, file, True, len(array), len(array[0]))
				else:
					matricies.append(array, file, False, len(array), len(array[0]))
	return matricies
def convertStr(s):
	"""Convert string to either int or float."""
	ret = '1'
	try:
		ret = int(s)
	except ValueError:
		#Try float.
		print "Oops!  That was no valid number.  Try again..."
	return ret
def selectMatrix(matricies):
	exit_flag = 1
	while exit_flag is not 0:
		print "\nPlease select a matrix"
		i = matricies.listEntries()
		prompt1 = raw_input(":")
		prompt1 = convertStr(prompt1)
		if prompt1 > i or prompt1 < 1:
			print "invalid input"
		else:
			new_matrix = matricies.head
			x=1
			while x<(prompt1):
				new_matrix = new_matrix.next
				x+=1
			if new_matrix is not None:
				print "You selected: " + str(new_matrix.filename)
			exit_flag = 0
	return new_matrix

#Main Runtime
def main():
	print str("\n"*10)
	matricies = refresh()
	
	exit_flag = 1
	while exit_flag > 0:
		print "\n~~~~~~~~~~~~~Menu:~~~~~~~~~~~~\nRefresh Matricies \t---- 1\nCall MatrixList.show()\t---- 2\nMultiply \t\t---- 3\nAdd \t\t\t---- 4\nTranspose \t\t---- 5\nExit \t\t\t---- 6"
		prompt = raw_input(":")
		prompt = convertStr(prompt)

		if prompt < 0 or prompt > 6:
			exit_flag = 1
		elif prompt == 1:
			matricies = refresh()
		elif prompt == 2:
			matricies.show()
		elif prompt == 3:
			#new_matrix = matricies.head
			matrix1 = selectMatrix(matricies)
			matrix2 = selectMatrix(matricies)
			if (matrix1.m == matrix2.n):
				#Create new matrix shell filled with zeroes
				matrix = [[0 for i in range(matrix2.m)] for j in range(matrix1.n)]
				#Loop through 
				for i in range(0, matrix1.n):	
					for k in range(0, matrix2.m):
						mult = 0
						for j in range(0, matrix1.m):
							mult += float(matrix1.array[i][j]) * float(matrix2.array[j][k])
						matrix[i][k] = mult

				#print new matrix
				for i in range(0, matrix1.n):
					print int(matrix[i])
			else:
				print "Invalid Selection - please try agian"
		elif prompt == 4:
			#new_matrix = matricies.head
			matrix1 = selectMatrix(matricies)
			matrix2 = selectMatrix(matricies)
			if (matrix1.n == matrix2.n) and (matrix1.m == matrix2.m):
				#print "n=" + str(n) + ", m=" + str(m)
				matrix = [[0 for i in range(matrix1.n)] for j in range(matrix1.m)]

				for i in range(0, matrix1.n):
					for j in range(0, matrix1.m):
						matrix[i][j] = float(matrix1.array[i][j]) + float(matrix2.array[i][j])

				print "Addition matrix is: "
				for i in range(0, matrix1.n):
					print int(matrix[i])
			else:
				print "Invalid Selection - please try agian"
		elif prompt == 5:
			#new_matrix = matricies.head
			trans_matrix = selectMatrix(matricies)
			n = trans_matrix.n
			m = trans_matrix.m
			#print "n=" + str(n) + ", m=" + str(m)
			matrix = [[0 for i in range(n)] for j in range(m)]

			print "Original Matrix:"
			trans_matrix.show()
			for i in range(0, n):
				for j in range(0, m):
					#print "i=" + str(i) + ", j=" + str(j) + ": " + str(trans_matrix.array[i][j])
					matrix[j][i] = trans_matrix.array[i][j]
			
			print "Transposed Matrix:"
			for i in range(0, m):
				print matrix[i]
		else:
			exit_flag = 0
			print "Program Ending..."

#execute main function
main()