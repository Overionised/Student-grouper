#include <QApplication>
#include <QProgressBar>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QThread>
#include <QInputDialog>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>

using namespace std;

string shuffler(QProgressBar *progressBar, QSlider *slider, const vector<string>& excludeNames, int groupSize) {
    srand((unsigned)time(0));
    int r1, r2, ct = 0;
    string trida[2][15] = {
        {"-Vojtech Bien-", "-David Boucek-", "-Jakub Dopan-", "-Josef Hasek-", "-Artur Havrylenko-", "-Jan Herza-", "-Milan Holecek-", "-Mikulas Chlup-", "-Ondrej Kacer-", "-Vojtech Kminek-", "-Nori Koci-", "-Veronika Kominkova-", "-Amelie Martini-", "-Stepan Skruzny-", "-Miroslav Klasna-"},
        {"Bien", "Boucek", "Dopan", "Hasek", "Havrylenko", "Herza", "Holecek", "Chlup", "Kacer", "Kminek", "Koci", "Kominkova", "Martini", "Skruzny", "Klasna"}
    };

    // Exclude the specified names
    for (const string& excludeName : excludeNames) {
        for (int i = 0; i < sizeof(trida[1]) / sizeof(string); i++) {
            if (trida[1][i] == excludeName) {
                trida[0][i] = "*";
                break;
            }
        }
    }

    // Set maximum value for progress bar based on the number of iterations
    int maxIterations = sizeof(trida[1]) / sizeof(string);
    progressBar->setMaximum(maxIterations);

    // Iteratively swap elements in the array
    for (int i = 0; i < maxIterations; i++) {
        r1 = (rand() % maxIterations);
        r2 = (rand() % maxIterations);
        swap(trida[0][r1], trida[0][r2]);

        // Update progress bar value
        progressBar->setValue(i + 1);

        // Delay to make progress visible (you may need to include <QThread>)
        QThread::msleep(100);
    }

    // Display shuffled pairs with the specified group size
    string shuffledPairs;
    for (int i = 0; i < maxIterations; i++) {
        if (trida[0][i] != "*") {
            shuffledPairs += trida[0][i];
            ct++;
            if (ct == 1) {
                shuffledPairs += " - ";
            }
        }
        if (ct == groupSize) {
            shuffledPairs += "\n\n";
            ct = 0;
        }
    }

    return shuffledPairs;
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    // Create a container window
    QWidget window;
    window.setFixedSize(500, 300);

    // Create a progress bar
    QProgressBar *progressBar = new QProgressBar(&window);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setGeometry(10, 10, 480, 30);

    // Create a slider (not used in this version)
    QSlider *slider = new QSlider(&window);
    slider->setOrientation(Qt::Horizontal);
    slider->setRange(0, 100);
    slider->setValue(0);
    slider->setGeometry(10, 50, 480, 30);

    // Create a button to trigger shuffling
    QPushButton *shuffleButton = new QPushButton("Shuffle Pairs", &window);
    shuffleButton->setGeometry(10, 90, 480, 30);

    // Create a button to set the group size
    QPushButton *groupSizeButton = new QPushButton("Set Group Size", &window);
    groupSizeButton->setGeometry(10, 130, 480, 30);

    window.show();

    int groupSize = 2; // Default group size

    // Connection to trigger shuffling when the button is clicked
    QObject::connect(shuffleButton, &QPushButton::clicked, [&]() {
        // Get user input for exclusion
        bool ok;
        QString excludeNamesInput = QInputDialog::getText(&window, "Exclude Names", "Enter names to exclude (comma-separated with spaces):", QLineEdit::Normal, "", &ok);

        if (ok) {
            // Parse the input into a vector of names
            vector<string> excludeNames;
            stringstream ss(excludeNamesInput.toStdString());
            string name;
            while (getline(ss, name, ',')) {
                // Remove leading and trailing whitespaces
                size_t start = name.find_first_not_of(' ');
                size_t end = name.find_last_not_of(' ');
                if (start != string::npos && end != string::npos) {
                    excludeNames.push_back(name.substr(start, end - start + 1));
                }
            }

            // Call shuffler function with the excluded names and group size
            string shuffledPairs = shuffler(progressBar, slider, excludeNames, groupSize);
            // Display shuffled pairs using a message box
            QMessageBox::information(&window, "Shuffled Pairs", QString::fromStdString(shuffledPairs));
        }
    });

    // Connection to set the group size when the button is clicked
    QObject::connect(groupSizeButton, &QPushButton::clicked, [&]() {
        // Get user input for group size
        bool ok;
        int newGroupSize = QInputDialog::getInt(&window, "Set Group Size", "Enter the new group size:", groupSize, 1, 100, 1, &ok);

        if (ok) {
            groupSize = newGroupSize;
        }
    });

    return app.exec();
}
