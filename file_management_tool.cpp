#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

// --- Utility: read multi-line input until a single '.' line ---
string readMultilineInput() {
    cout << "Enter text (single '.' on its own line to finish):\n";
    string buffer, line;
    while (true) {
        if (!std::getline(cin, line)) break; // EOF or error
        if (line == ".") break;
        buffer += line + '\n';
    }
    return buffer;
}

// --- File operations ---
void writeFile(const string &path) {
    ofstream out(path, ios::out | ios::trunc);
    if (!out) {
        cerr << "[Error] Cannot open '" << path << "' for writing.\n";
        return;
    }
    string data = readMultilineInput();
    out << data;
    out.close();
    cout << "[OK] Wrote " << data.size() << " bytes to '" << path << "' (overwrite).\n\n";
}

void appendFile(const string &path) {
    ofstream out(path, ios::out | ios::app);
    if (!out) {
        cerr << "[Error] Cannot open '" << path << "' for appending.\n";
        return;
    }
    string data = readMultilineInput();
    out << data;
    out.close();
    cout << "[OK] Appended " << data.size() << " bytes to '" << path << "'.\n\n";
}

void readFile(const string &path) {
    ifstream in(path);
    if (!in) {
        cerr << "[Error] Cannot open '" << path << "' for reading (does the file exist?).\n";
        return;
    }
    cout << "\n----- Begin contents of '" << path << "' -----\n";
    string line;
    size_t lineNo = 1;
    while (std::getline(in, line)) {
        cout << lineNo++ << ": " << line << '\n';
    }
    cout << "------ End contents ------\n\n";
}

// --- Menu + helpers ---
void flushStdin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string promptPath(const string &defaultPath) {
    cout << "Enter file path [default: " << defaultPath << "]: ";
    string path;
    std::getline(cin, path);
    if (path.empty()) return defaultPath;
    return path;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const string DEFAULT_PATH = "data.txt"; // Will be created if it doesn't exist

    cout << "============================\n";
    cout << "   File Management Tool\n";
    cout << "   (C++ file handling demo)\n";
    cout << "============================\n\n";

    while (true) {
        cout << "Choose an option:\n";
        cout << " 1) Write (overwrite)\n";
        cout << " 2) Append\n";
        cout << " 3) Read\n";
        cout << " 4) Quit\n";
        cout << "> ";

        int choice = 0;
        if (!(cin >> choice)) {
            flushStdin();
            cout << "Please enter a valid number.\n\n";
            continue;
        }
        flushStdin(); // remove trailing newline

        switch (choice) {
            case 1: {
                string path = promptPath(DEFAULT_PATH);
                writeFile(path);
                break;
            }
            case 2: {
                string path = promptPath(DEFAULT_PATH);
                appendFile(path);
                break;
            }
            case 3: {
                string path = promptPath(DEFAULT_PATH);
                readFile(path);
                break;
            }
            case 4:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Unknown option. Try again.\n\n";
        }
    }
}
