#include <cassert>
#include <iostream>
#include <fstream>

#include "Prompt.hpp"
#include "Workspace.hpp"

void prompt_smoke_test() {
    Prompt p("Reviewer", "Review this requirement.");
    assert(p.title() == "Reviewer");
    assert(!p.empty());
}

void workspace_smoke_test() {
    Workspace w("Demo");
    w.addPrompt(Prompt("Reviewer", "Review this requirement."));
    assert(w.promptCount() == 1);
}

void document_test() {

    Document d1;
	assert(d1.title().empty());
    assert(d1.sourcePath().empty());
	assert(d1.contents().empty());
	assert(d1.characterCount() == 0);


	Document d2("Title", "Contents");
	Document d3("Title", "Contents");
	assert(d2.title() == "Title");
	assert(d2.contents() == "Contents");
	assert(d2.characterCount() == 8);
	assert(d2.sourcePath().empty());
	assert(!d2.empty());
	assert(d2 != d1);
	assert(d2 == d3);



    Document d4;
	assert(d4.load("../text/sample.txt"));
	assert(d4.title() == "sample.txt");
	assert(d4.sourcePath() == "../text/sample.txt");
	assert(d4.contents() == "Requirements should be clear, testable, and traceable.\n");
	assert(d4.characterCount() == 55);

	assert(d4.load("nonexistent.txt") == false);
	assert(d4.title() == "sample.txt");
	assert(d4.sourcePath() == "../text/sample.txt");
	assert(d4.contents() == "Requirements should be clear, testable, and traceable.\n");
	assert(d4.characterCount() == 55);

}

int main() {
    //prompt_smoke_test();
    //workspace_smoke_test();
	document_test();

    // TODO: Add your own meaningful M0 tests.
    // See the Testing Requirements section of the specification.

    std::cout << "M0 tests passed\n";
    return 0;
}
