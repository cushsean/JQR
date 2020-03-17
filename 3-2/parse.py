import argparse
import re

parser = argparse.ArgumentParser(
    description='Validates email and phone number are valid')

parser.add_argument('-p', '--phone', metavar='', required=True, 
    help='takes a 7 or 10 digit phone number')
parser.add_argument('-e', '--email', metavar='', required=True, 
    help='takes a valid email address')
parser.add_argument('-q', '--quiet', action='store_true', help='print quiet')
parser.add_argument('-v', '--verbose', action='store_true', help='print verbose')

args = parser.parse_args()

def validate_phone(phone):
    if args.quiet is False:
        print()
        print("Input: " + phone)
    __check = re.search(r'^[(]?\d{3}[)]?\D?\d{3}\D?\d{4}$', phone)
    if args.verbose:
        print("Checking that phone number conatins:")
        print("\t1.  4 Line Numbers")
        print("\t2.  3 Prefix Numbers")
        print("\t3.  A space, hyphen, or no-space between Line and Prefix")
        print("\t4a. Optionally 3 Area Code Numbers")
        print("\t4b. If Area Code present; optionally sparated by")
        print("\t    a space, hyphen, or parenthesis")
        print()
    if __check != None:
        if args.quiet is False:
            print("Phone number is valid")
        return True
    else:
        if args.quiet is False:
            print("Phone number is NOT valid")
        return False


def validate_email(email):
    if args.quiet is False:
        print()
        print("Input: " + email)
    __check = re.search(
        r'^(\w|\d)([^"(),:;<>@[\\\]]{0,62}(\w|\d))?[@][^.@]{1,253}[.](\w|\d|[.]){2,}$', 
        email)
    if args.verbose:
        print("There is a lot that goes into an email.")
        print("We have ignored the outliers.")
        print("We are checking the common cases for validity.")
        print()
    if __check != None:
        if args.quiet is False:
            print("Email is valid")
        return True
    else:
        if args.quiet is False:
            print("Email is NOT valid")
        return False


if __name__ == '__main__':
    __phone = validate_phone(args.phone)
    __email = validate_email(args.email)

    if args.quiet:
        if __phone and __email:
            print("Input Valid")
        else:
            print("Input Invalid")