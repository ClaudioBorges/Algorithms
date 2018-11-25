#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// There're at most 11 different chars in a valid IP address "\.[0-9]"
#define CHARS 11

size_t indexForChar(char c) { return (c == '.') ? 10 : (c - '0'); }

struct trieNode {
    bool isLeaf;
    const char *URL;
    struct trieNode *child[CHARS];
};

struct trieNode *newTrieNode(void) {
    struct trieNode *newNode = new trieNode;
    newNode->isLeaf = false;
    newNode->URL = nullptr;
    for (size_t i = 0; i < CHARS; ++i) {
        newNode->child[i] = nullptr;
    }
    return newNode;
}

void
insert(struct trieNode *root, const char *ipAddr, const char *URL) {
    struct trieNode *node = root;
    size_t len = strlen(ipAddr);

    for (size_t level = 0; level < len; ++level) {
        size_t index = indexForChar(ipAddr[level]);

        if (!node->child[index]) {
            node->child[index] = newTrieNode();
        }

        node = node->child[index];
    }

    node->isLeaf = true;
    char * tmp = new char[strlen(URL) + 1];
    strcpy(tmp, URL);
    node->URL = tmp;
}
const char *
searchDNSCache(struct trieNode *root, const char *ipAddr) {
    struct trieNode *node = root;
    size_t len = strlen(ipAddr);

    for (size_t level = 0; level < len; ++level) {
        size_t index = indexForChar(ipAddr[level]);
        if (!node->child[index]) {
            return nullptr;
        }
        node = node->child[index];
    }
    if (node && node->isLeaf) {
        return node->URL;
    }
    return nullptr;
}

int
main() {
    const char * ipAddr[] = {
        "108.177.126.104",
        "104.123.103.164",
        "31.13.73.35",
    };

    const char * URL[] = {
        "www.google.com",
        "www.amazon.com",
        "www.facebook.com",
    };

    size_t n = sizeof(URL) / sizeof(URL[0]);

    struct trieNode *root = newTrieNode();

    for (size_t i = 0; i < n; ++i) {
        insert(root, ipAddr[i], URL[i]);
    }

    for (size_t i = 0; i < n; ++i) {
        const char *ip = ipAddr[i];
        const char *found_url = searchDNSCache(root, ip);
        if (found_url != nullptr) {
            printf("Reverse DNS lookup for IP %s is URL %s.",
                   ip, found_url);
        } else {
            printf("Reverse DNS lookup for %s not resolved.", ip);
        }
        printf("\n");
    }
}

