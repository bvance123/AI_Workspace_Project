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

void message_test() {
   
    Message m1(MessageRole::User, "who's that pokemon");
    assert(m1.role() == MessageRole::User);
    assert(m1.text() == "who's that pokemon");
    assert(m1.empty() == false);


    Message m2(MessageRole::Assistant, "");
    assert(m2.empty() == true);


    m2.setRole(MessageRole::System);
    m2.setText("System initialized.");
    assert(m2.role() == MessageRole::System);
    assert(m2.text() == "System initialized.");
    assert(m2.empty() == false);

    
    Message m3(MessageRole::System, "System initialized.");
    assert(m2 == m3);

    Message m4(MessageRole::User, "System initialized.");
    assert(m2 != m4);
}

int main() {
    prompt_smoke_test();
    workspace_smoke_test();
	document_test();
    message_test();

	Workspace ws("AI Research");

	assert(ws.name() == "AI Research");
	ws.setName("AI Development");
	assert(ws.name() == "AI Development");

	assert(ws.documentCount() == 0);
    Document doc1;
	ws.addDocument(doc1);
	assert(ws.documentCount() == 1);

	assert(ws.promptCount() == 0);
	Prompt prompt1("Reviewer", "Review this requirement.");
	ws.addPrompt(prompt1);
	assert(ws.promptCount() == 1);
	assert(ws.promptAt(0) == prompt1);
	assert(ws.promptAt(0).title() == "Reviewer");

	assert(ws.messageCount() == 0);
	Message msg1(MessageRole::User, "Who's that pokemon?");	
	ws.addMessage(msg1);	
	assert(ws.messageCount() == 1);
	assert(ws.messageAt(0) == msg1);
	assert(ws.messageAt(0).role() == MessageRole::User);
	assert(ws.messageAt(0).text() == "Who's that pokemon?");

	Workspace ws2("AI Development");
	ws2.addDocument(doc1);
	ws2.addPrompt(prompt1);	
	ws2.addMessage(msg1);	

	assert(ws == ws2);

	Workspace ws3("Never Knows Best");

	assert(ws != ws3);

    std::cout << "M0 tests passed\n";
    return 0;
}
