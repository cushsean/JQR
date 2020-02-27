"""
3.2.2
Explicit and implicit declaration of data types
"""

evar_int = int(5)
evar_float = float(10.3)
evar_str = str("words")
evar_list = list(("item1", "item2", "item3"))
evar_dict = dict(name="sean", age=24)
evar_tuple = tuple(evar_list)

ivar_int = 5
ivar_float = 10.3
iar_str = "words"
ivar_list = ["item1", "item2", "item3"]
ivar_multiList = [["item1.1", "item1.2", "item1.3"], ["item2.1", "item2.2", "item2.3"]]
ivar_dict = {"name" : "sean", "age" : 24}
ivar_tuple = (16, 49, 33)

#Singleton
class Apples(object):
    _instance = None
    def __new__(self):
        if not self._instance:
            self._instance = super(Apples, self).__new__(self)
            self.data = 10
        return self._instance

inst_1 = Apples()
print(inst_1.data)
#output: 10
inst_1.data = 20

inst_2 = Apples()
print(inst_2.data)
#output: 20

"""
3.2.3
Demonstrate basic arithmetic
"""

num1 = 5
num2 = 10
plus = num1 + num2
minus = num2 - num1
mult = num1 * num2
div = num2 / num1
mod = minus % div

print("num1 : " + str(num1))
print("num2 : " + str(num2))
print("num1 + num2 : " + str(plus))
print("num2 - num1 : " + str(minus))
print("num1 * num2 : " + str(mult))
print("num2 / num1 : " + str(div))
print("minus % div : " + str(mod))

print("expected : 0")
ans = int(pow(2,8)*(4+28)/1024-8)
print("2^8*(4+28)/1024-8 = " + str(ans))

"""
3.2.5 - Functions
3.2.6 - Data validation
"""


def factorial(x):
    #3.2.7.d
    if x > 1:
        #recursion - 3.2.5.c
        x = x*factorial(x-1)
        return x
    else:
        return 1

def func():
    print("This function calculates the factorial of any whole positive number")
    
    #user input - 3.2.5.b
    try:
        x = input("Please provide a number to factor : ")
    except EOFError:
        print("User input expected")
        
    #data validation - 3.2.6
    try:
        x = int(x)
    except ValueError:
        print("ERROR: Expected an INT but recieved a", end =" ")
        try:
            x = float(x)
            print("FLOAT")
        except:
            print("STRING")
    try:
        #3.2.7.c
        if x <= 0:
            raise ValueError
    except ValueError:
        print("ERROR: Expected positive value but recieved value less than or equal to 0")

    ans = factorial(x)

    #return muliple values - 3.2.5.a
    return (ans, x)

ans, x = func()
print("The factorial " + str(x) + "! is " + str(ans))

"""
3.2.1 - Descript the purpose and use of:

    a. The return statement:
        The return allows you to return to the parent function, data can be returned was well.
    
    b. Data Types:
        Explains/controlls the context of variables: strings, floats, ints, tuples, lists, dictionaries, etc.

    c. Functions:
        A submodule that performs (usally fequently used) blocks of code. Can return a value.
    
    d. Parameters:
        Variables that are passed to functions.

    e. Scope:
        The block of code that a varable is visable/usable.

    f. Return values (reture type and reference):
        In python, you return objects. Objects are Python's abstraction for data. Every object has an
        identity, type, and value. (PRM 3.1)

    g. Import files
        Modules/libraries that contain methods/classes/functions
    
    h. Dictionaries:
        Otherwise known as "associative arrays", dictionaries are indexed by keys rather than numbers.
        Keys can be any immutable type, including strings and numbers. Tuples can be keys if they contain
        only strings, numbers, or tuples. 

    i. Lists:
        Similar to c arrays, lists are mutable (changable) data of any type that (generally) 
        is stored in memory sequentially. Uses []

    j. Tuples:
        Similar to Lists but uses () and is imutable (unchangable).

    k. Structs:
        Like c structs. Custom data type.

    l. Unions:
        A space of memory that is large enough to hold two different types of data but can be referenced by either.

    m. Singleton:
        A type of class that has one "logical" instance shared amoung all instances of the class.

    n. Mutable:
        Chanage data. ex) Lists

    o. Immutable:
        Unchangable data. ex) Tuples
"""

"""
3.2.9 - Describe the terms and fundamentals associated with OOP using Python:

    a. Class:


    b. Object:


    c. Difference between an object when discussing a class:


    d. Advantages to OOP:


    e. Inheritance:


    f. The keyword "Super":


    g. Initialization function of a constructor:


    h. The keyword "self":


    i. The getter and setter functions:


    j. Attributes of a class:


    k. Factory design pattern:


    l. Sinleton desing pattern:


    m. Adapter design pattern:


    n. Bridge design pattern:


"""