import xlwt
import os

def get_accuracy(origin_labels, classify_labels, parameters):
    assert len(origin_labels) == len(classify_labels)

    xls_contents = []

    xls_contents.extend([("train num", parameters[0]), ("test num", parameters[1])])
    xls_contents.append(("feature num", parameters[2]))

    pos_right, pos_false = 0, 0
    neg_right, neg_false = 0, 0
    for i in range(len(origin_labels)):
        if origin_labels[i] == 1:
            if classify_labels[i] == 1:
                pos_right += 1
            else:
                neg_false += 1
        else:
            if classify_labels[i] == 0:
                neg_right += 1
            else:
                pos_false += 1
    xls_contents.extend([("neg-right", neg_right), ("neg-false", neg_false)])
    xls_contents.extend([("pos-right", pos_right), ("pos-false", pos_false)])

    pos_precision = pos_right / (pos_right + pos_false) * 100
    pos_recall = pos_right / (pos_right + neg_false) * 100
    pos_f1 = 2 * pos_precision * pos_recall / (pos_precision + pos_recall)
    xls_contents.extend([("pos-precision", pos_precision), ("pos-recall", pos_recall), ("pos-f1", pos_f1)])

    neg_precision = neg_right / (neg_right + neg_false) * 100
    neg_recall = neg_right / (neg_right + pos_false) * 100
    neg_f1 = 2 * neg_precision * neg_recall / (neg_precision + neg_recall)
    xls_contents.extend([("neg-precision", neg_precision), ("neg-recall", neg_recall), ("neg-f1", neg_f1)])

    total_recall = (neg_right + pos_right) / (neg_right + neg_false + pos_right + pos_false) * 100
    xls_contents.append(("total-recall", total_recall))

    print("    pos-right\tpos-false\tneg-right\tneg-false\tpos-precision\tpos-recall\t"
          "pos-f1\tneg-precision\tneg-recall\tneg-f1\ttotal-recall")
    print("    " + "---" * 45)
    print("    %8d\t%8d\t%8d\t%8d\t%8.4f\t%8.4f\t%8.4f\t%8.4f\t%8.4f\t%8.4f\t%8.4f" %
          (pos_right, pos_false, neg_right, neg_false, pos_precision, pos_recall,
           pos_f1, neg_precision, neg_recall, neg_f1, total_recall))

    return xls_contents