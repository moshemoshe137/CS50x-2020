import sys

if len(sys.argv) != 2:
    print("NO!")
    sys.exit(1)
    
print(f"Hello, {sys.argv[1]}")