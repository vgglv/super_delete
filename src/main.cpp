#include <filesystem>
#include <iostream>

void printHelp();
void deleteAnyFileOrFolder(const std::string &path);
std::optional<std::string> tryToGetAbsolutePath(const std::string &path);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printHelp();
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--help" || arg == "-h") {
            printHelp();
            break;
        }
        deleteAnyFileOrFolder(arg);
    }
}

void printHelp() {
    std::cout << "Usage:\n";
    std::cout << " super_delete.exe <dir>...\n";
    std::cout << "\n";
}

void deleteAnyFileOrFolder(const std::string &path) {
    auto pathOptional = tryToGetAbsolutePath(path);
    if (!pathOptional.has_value()) {
        std::cout << "Tried to find absolute path of: '" << path << "', but failed\n";
        return;
    }
    auto absolutePath = pathOptional.value();
    if (!std::filesystem::exists(absolutePath)) {
        std::cout << "Path: '" << absolutePath << "' does not exists\n";
        return;
    }
    std::cout << "Deleting path: '" << absolutePath << "'\n";
    try {
        std::filesystem::remove_all(absolutePath);
    } catch (const std::filesystem::filesystem_error &e) {
        std::cout << e.what() << "\n";
        return;
    }
}

std::optional<std::string> tryToGetAbsolutePath(const std::string &path) {
    try {
        if (std::filesystem::exists(path)) {
            return std::filesystem::absolute(path).string();
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cout << e.what() << "\n";
    }
    return std::nullopt;
}