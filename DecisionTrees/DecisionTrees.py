import pandas as pd

# Load a CSV file
def load_csv(filename):
	file = open(filename, "rb")
	lines = reader(file)
	dataset = list(lines)
	return dataset

def main():
    filename = "data_banknote_authentication.txt"
    df = pd.read_csv(filename)
    sub_df = df.head(8)

    print(sub_df)
    #print(sub_df.index)
    sub_df.iloc[0:3] = 34
if __name__ == '__main__':
    main()
