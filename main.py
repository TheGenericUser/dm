import numpy as np
from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score

clf = DecisionTreeClassifier(random_state=42)
clf.fit(X_train_iris, y_train_iris)
y_pred_iris = clf.predict(X_test_iris)
accuracy_iris = accuracy_score(y_test_iris, y_pred_iris)



#Dividing Data into train and test hold_out

from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
import numpy as np

# Load datasets
iris = datasets.load_iris()
wine = datasets.load_wine()

# Split datasets into training (75%) and testing (25%)
X_train_iris, X_test_iris, y_train_iris, y_test_iris = train_test_split(
    iris.data, iris.target, test_size=0.25, random_state=42)

X_train_wine, X_test_wine, y_train_wine, y_test_wine = train_test_split(
    wine.data, wine.target, test_size=0.25, random_state=42)
