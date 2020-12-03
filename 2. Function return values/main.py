import myModule

# return none
print("Should be: None")
print(myModule.retNone())

# return bool
print("Should be: True")
print(myModule.retBool())

# return int
print("Should be: 123")
print(myModule.retInt())

# return float
print("Should be: 123.456")
print(myModule.retFloat())

# return string
print("Should be: hello")
print(myModule.retString())

# return tuple
print("Should be: (123, 456)")
print(myModule.retTuple())

# return tuple of mixed types
print("Should be: (123, 'hello')")
print(myModule.retMixedTuple())

# return 2d tuple
print("Should be: ((123, 456), (123, 456))")
print(myModule.ret2DTuple())

# return tuple of varying size
print("Should be: (1, 2, 3, 4, 5, 6)")
print(myModule.retTupleOfVarSize())

# return 2d tuple of varying size
print("Should be: ((1, 2, 3, 4), (5, 6, 7), (8, 9))")
print(myModule.ret2DTupleOfVarSize())

# return list
print("Should be: [123, 456]")
print(myModule.retList())

# return 2d list
print("Should be: [[123, 456], [123, 456]]")
print(myModule.ret2DList())

# return list of varying size
print("Should be: [1, 2, 3, 4, 5, 6]")
print(myModule.retListOfVarSize())

# return 2d list of varying size
print("Should be: [[1, 2, 3, 4], [5, 6, 7], [8, 9]]")
print(myModule.ret2DListOfVarSize())
