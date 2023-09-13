# Moshe Rubin
# 2/3/2021
# Print Mario pyramids
# https://cs50.harvard.edu/x/2021/psets/6/mario/more/

def main():

    # get the height
    height = 0
    while not (1 <= height <= 8):
        height_str = input("Height: ")
        try:
            height = int(height_str)
        except:
            height = 0
    for row in range(height):
        print(" " * (height - row - 1), end='')
        print("#" * (row + 1), end='')
        print(" " * 2, end='')
        print("#" * (row + 1))


if __name__ == "__main__":
    main()
