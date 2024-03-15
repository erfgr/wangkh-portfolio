from builtins import range
from builtins import object
import numpy as np


class KNearestNeighbor(object):
    def __init__(self):
        pass

    def train(self, X, y):
        self.X_train = X
        self.y_train = y

    def predict(self, X, k=1, num_loops=0):
        if num_loops == 0:
            dists = self.compute_distances_no_loops(X)
        elif num_loops == 1:
            dists = self.compute_distances_one_loop(X)
        elif num_loops == 2:
            dists = self.compute_distances_two_loops(X)
        else:
            raise ValueError("Invalid value %d for num_loops" % num_loops)

        return self.predict_labels(dists, k=k)

    def compute_distances_two_loops(self, X):
        num_test = X.shape[0]
        num_train = self.X_train.shape[0]
        dists = np.zeros((num_test, num_train))
        for i in range(num_test):
            for j in range(num_train):
                dists[i, j] = np.sqrt(np.sum(np.square(X[i] - self.X_train[j])))
        return dists

    def compute_distances_one_loop(self, X):
        num_test = X.shape[0]
        num_train = self.X_train.shape[0]
        dists = np.zeros((num_test, num_train))
        for i in range(num_test):
            dists[i] = np.sqrt(np.sum(np.square(self.X_train - X[i]), axis=1))
        return dists

    def compute_distances_no_loops(self, X):
        num_test = X.shape[0]
        num_train = self.X_train.shape[0]
        dists = np.zeros((num_test, num_train))
        dists = np.sqrt(np.sum(np.square(self.X_train), axis=1) + np.sum(np.square(X), axis=1)[:, np.newaxis] - 2 * np.dot(X, self.X_train.T))
        return dists

    def predict_labels(self, dists, k=1):
        num_test = dists.shape[0]
        y_pred = np.zeros(num_test)
        for i in range(num_test):
            closest_y = []
            closest_y = np.argsort(dists[i])[:k]
            closest_y = [self.y_train[x] for x in closest_y]
            from collections import Counter
            counter = Counter(closest_y)
            y_pred[i] = counter.most_common(1)[0][0]
        return y_pred

class NaiveBayes(object):
    def __init__(self):
        pass

    def train(self, X, y):
        self.X_train = X
        self.y_train = y
        self.num_train = X.shape[0]
        self.num_feature = X.shape[1]
        self.num_class = np.max(y) + 1
        self.prior = np.zeros(self.num_class)
        self.mean = np.zeros((self.num_class, self.num_feature))
        self.var = np.zeros((self.num_class, self.num_feature))
        for i in range(self.num_class):
            self.prior[i] = np.sum(self.y_train == i) / self.num_train
            self.mean[i] = np.mean(self.X_train[self.y_train == i], axis=0)
            self.var[i] = np.var(self.X_train[self.y_train == i], axis=0)

    def predict(self, X):
        num_test = X.shape[0]
        y_pred = np.zeros(num_test)
        for i in range(num_test):
            log_probs = np.zeros(self.num_class)
            for j in range(self.num_class):
                log_probs[j] = np.sum(-0.5 * np.log(2 * np.pi * self.var[j]) - ((X[i] - self.mean[j]) ** 2) / (2 * self.var[j]))
            log_probs += np.log(self.prior)
            y_pred[i] = np.argmax(log_probs)
        return y_pred
    
class SVM(object):
    def __init__(self):
        pass

    def train(self, X, y, learning_rate=1e-3, reg=1e-5, num_iters=100, batch_size=200, verbose=False):
        num_train, dim = X.shape
        num_classes = np.max(y) + 1
        if self.W is None:
            self.W = 0.001 * np.random.randn(dim, num_classes)
        loss_history = []
        for it in range(num_iters):
            X_batch = None
            y_batch = None
            batch_index = np.random.choice(num_train, batch_size, replace=True)
            X_batch = X[batch_index]
            y_batch = y[batch_index]
            loss, grad = self.loss(X_batch, y_batch, reg)
            loss_history.append(loss)
            self.W -= learning_rate * grad
            if verbose and it % 100 == 0:
                print('iteration %d / %d: loss %f' % (it, num_iters, loss))
        return loss_history

    def predict(self, X):
        y_pred = np.zeros(X.shape[0])
        scores = X.dot(self.W)
        y_pred = np.argmax(scores, axis=1)
        return y_pred

    def loss(self, X_batch, y_batch, reg):
        loss = 0.0
        dW = np.zeros(self.W.shape)
        num_train = X_batch.shape[0]
        scores = X_batch.dot(self.W)
        correct_class_score = scores[np.arange(num_train), y_batch]
        margins = np.maximum(0, scores - correct_class_score[:, np.newaxis] + 1.0)
        margins[np.arange(num_train), y_batch] = 0
        loss = np.sum(margins) / num_train + 0.5 * reg * np.sum(self.W * self.W)
        coeff_mat = np.zeros((num_train, self.W.shape[1]))
        coeff_mat[margins > 0] = 1
        coeff_mat[np.arange(num_train), y_batch] = 0
        coeff_mat[np.arange(num_train), y_batch] = -np.sum(coeff_mat, axis=1)
        dW = (X_batch.T).dot(coeff_mat)
        dW = dW / num_train + reg * self.W
        return loss, dW
    
class MaxEntClassifier(object):
    def __init__(self, num_features, num_classes):
        self.W = np.zeros((num_features, num_classes))
        self.b = np.zeros(num_classes)

    def train(self, X, y, learning_rate=0.1, num_epochs=1000):
        num_samples, num_features = X.shape
        num_classes = np.max(y) + 1

        for epoch in range(num_epochs):
            for i in range(num_samples):
                # Compute the scores for each class
                scores = np.dot(X[i], self.W) + self.b

                # Compute softmax probabilities
                exp_scores = np.exp(scores - np.max(scores))
                probs = exp_scores / np.sum(exp_scores)

                # Compute the gradient of the log-likelihood
                gradient = -X[i][:, np.newaxis] @ probs[y[i]].reshape(1, -1)
                gradient += np.dot(X[i][:, np.newaxis], probs.reshape(1, -1))

                # Update weights and bias
                self.W -= learning_rate * gradient
                self.b -= learning_rate * (probs - (y[i] == np.arange(num_classes)))

    def predict(self, X):
        num_samples, _ = X.shape
        scores = np.dot(X, self.W) + self.b
        probs = np.exp(scores - np.max(scores, axis=1)[:, np.newaxis]) / np.sum(np.exp(scores), axis=1)[:, np.newaxis]
        return np.argmax(probs, axis=1)
    
class GRU(object):
    def __init__(self):
        pass

    def train(self, X, y, learning_rate=1e-3, reg=1e-5, num_iters=100, batch_size=200, verbose=False):
        num_train, dim = X.shape
        num_classes = np.max(y) + 1
        if self.W is None:
            self.W = 0.001 * np.random.randn(dim, num_classes)
        loss_history = []
        for it in range(num_iters):
            X_batch = None
            y_batch = None
            batch_index = np.random.choice(num_train, batch_size, replace=True)
            X_batch = X[batch_index]
            y_batch = y[batch_index]
            loss, grad = self.loss(X_batch, y_batch, reg)
            loss_history.append(loss)
            self.W -= learning_rate * grad
            if verbose and it % 100 == 0:
                print('iteration %d / %d: loss %f' % (it, num_iters, loss))
        return loss_history

    def predict(self, X):
        y_pred = np.zeros(X.shape[0])
        scores = X.dot(self.W)
        y_pred = np.argmax(scores, axis=1)
        return y_pred

    def loss(self, X_batch, y_batch, reg):
        loss = 0.0
        dW = np.zeros(self.W.shape)
        num_train = X_batch.shape[0]
        scores = X_batch.dot(self.W)
        correct_class_score = scores[np.arange(num_train), y_batch]
        margins = np.maximum(0, scores - correct_class_score[:, np.newaxis] + 1.0)
        margins[np.arange(num_train), y_batch] = 0
        loss = np.sum(margins) / num_train + 0.5 * reg * np.sum(self.W * self.W)
        coeff_mat = np.zeros((num_train, self.W.shape[1]))
        coeff_mat[margins > 0] = 1
        coeff_mat[np.arange(num_train), y_batch] = 0
        coeff_mat[np.arange(num_train), y_batch] = -np.sum(coeff_mat, axis=1)
        dW = (X_batch.T).dot(coeff_mat)
        dW = dW / num_train + reg * self.W
        return loss, dW
    
