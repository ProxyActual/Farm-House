import numpy as np

class NeuralNetwork:
    def __init__(self, input_size, hidden_size, output_size):
        self.input_size = input_size
        self.hidden_size = hidden_size
        self.output_size = output_size

        # Initialize weights
        self.W1 = np.random.randn(self.input_size, self.hidden_size)
        self.W2 = np.random.randn(self.hidden_size, self.output_size)

    def sigmoid(self, z):
        return 1 / (1 + np.exp(-z))

    def sigmoid_derivative(self, z):
        return z * (1 - z)

    def forward(self, X):
        self.z1 = np.dot(X, self.W1)
        self.a1 = self.sigmoid(self.z1)
        self.z2 = np.dot(self.a1, self.W2)
        self.output = self.sigmoid(self.z2)
        return self.output

    def backward(self, X, y, output):
        self.output_error = y - output
        self.output_delta = self.output_error * self.sigmoid_derivative(output)

        self.a1_error = self.output_delta.dot(self.W2.T)
        self.a1_delta = self.a1_error * self.sigmoid_derivative(self.a1)

        self.W1 += X.T.dot(self.a1_delta)
        self.W2 += self.a1.T.dot(self.output_delta)

    def train(self, X, y, epochs=10000):
        for epoch in range(epochs):
            output = self.forward(X)
            self.backward(X, y, output)

# Example usage
if __name__ == "__main__":
    X = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
    y = np.array([[0], [1], [1], [0]])

    nn = NeuralNetwork(input_size=2, hidden_size=2, output_size=1)
    nn.train(X, y)

    print("Predicted output:")
    print(nn.forward(X))