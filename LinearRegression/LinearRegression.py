from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
import pandas as pd
import matplotlib.pyplot as plt

def main():
    pd.set_option('display.max_rows', 999)
    pd.set_option('display.max_columns', 500)
    pd.set_option('display.width', 10000)
    model = LinearRegression()
    usa_housing = pd.read_csv('USA_Housing.csv').head(1000)
    print("All columns:", usa_housing.columns.values)
    x_values = usa_housing[['Avg. Area Income', 'Avg. Area House Age', 'Avg. Area Number of Rooms',
               'Avg. Area Number of Bedrooms', 'Area Population']]
    print("Featutres:", x_values.columns.values)
    
    y_values = usa_housing['Price']
    
    x_train, x_test, y_train, y_test = train_test_split(x_values, y_values, test_size=0.4, random_state=101)
    print("Length of x_train:", len(x_train))
    print("Length of x_test:", len(x_test))
    print("Length of y_train:", len(y_train))
    print("Length of y_test:", len(y_test))
    
    print("Test/total ratio:", len(x_test)/(len(x_train)+len(x_test)))
    model.fit(x_train, y_train)
    predictions = model.predict(x_test)

    plt.scatter(y_test,predictions)
    plt.show()

if __name__ == "__main__":
    main()