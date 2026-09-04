#include "Document.hpp" 
#include <fstream>
#include <sstream>
#include <filesystem>


Document::Document(std::string title, std::string contents): title_(std::move(title)), contents_(std::move(contents)) {
    // TODO: implement according to the M1 specification.

}

bool Document::operator==(const Document& other) const {
	return title_ == other.title_ && contents_ == other.contents_ && sourcePath_ == other.sourcePath_;

}

bool Document::operator!=(const Document& other) const {
	return !(*this == other); // reuse the equality operator for inequality check

}

bool Document::load(const std::string& path) {
	std::ifstream file(path);

    if(!file.is_open()) {
        return false; // Failed to open the file
	}

	std::stringstream buffer;
	buffer << file.rdbuf(); // Read the file contents into the buffer (make sure it all carries over before writing to contents_)

    if(file.bad()) {
        return false; // Error occurred while reading the file
	}   

	contents_ = buffer.str(); // Stor the contents in the member variable
	sourcePath_ = path; // store the source path

	std::filesystem::path filePath(path);
	title_ = filePath.filename().string();  // get the title
}

const std::string& Document::title() const noexcept {
	return title_;

}

const std::string& Document::sourcePath() const noexcept {
	return sourcePath_;

}

const std::string& Document::contents() const noexcept {
	return contents_;
  
}

void Document::setTitle(std::string title) {
	title_ = std::move(title);
  
}

std::size_t Document::characterCount() const noexcept {
	return contents_.size();
    
}

bool Document::empty() const noexcept {
	return contents_.empty();
   
}
