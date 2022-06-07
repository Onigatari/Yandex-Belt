#include <string>
#include <list>

#include "test_runner.h"

using namespace std;

class Editor {
public:
    Editor() : cursor(text.end()) {}

    void Left() {
        if (cursor == text.begin())
            return;

        --cursor;
    }

    void Right() {
        if (cursor == text.end())
            return;

        ++cursor;
    }

    void Insert(char token) {
        text.insert(cursor, token);
    }

    void Copy(size_t tokens = 1) {
        buffer = {cursor, next(cursor, tokens)};
    }

    void Cut(size_t tokens = 1) {
        Copy(tokens);

        auto u = cursor;
        while (tokens--) {
            if (++u == text.end()) {
                break;
            }
        }

        cursor = text.erase(cursor, u);
    }

    void Paste() {
        text.insert(cursor, buffer.begin(), buffer.end());
    }

    string GetText() const {
        return {text.begin(), text.end()};
    }

private:
    using Iterator = list<char>::iterator;
    list<char> text;
    list<char> buffer;
    Iterator cursor;

    Iterator Move(Iterator it, int steps) {
        if (steps > 0) {
            while (it != text.end()) {
                ++it;
                --steps;
            }
        } else {
            while (steps < 0 && it != text.begin()) {
                --it;
                ++steps;
            }
        }

        return it;
    }
};

void TypeText(Editor &editor, const string &text) {
    for (char c: text) {
        editor.Insert(c);
    }
}

void TestEditing() {
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        for (size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }
        editor.Cut(first_part_len);
        for (size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }
        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() {
    Editor editor;

    const string text = "esreveR";
    for (char c: text) {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {

    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}