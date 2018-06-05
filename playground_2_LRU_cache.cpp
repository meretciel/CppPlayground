/*
 * playground_3_LRU.cpp
 *
 *  Created on: Jun 3, 2018
 *      Author: Ruikun
 */


#include <iostream>
#include <string>
#include <map>
#include <list>
#include <utility>
#include <exception>

using namespace std;

namespace {

class LRUCache {
private:
    using _Key       = string;
    using _Value     = int;
    using _Node      = pair<_Key, _Value>;
    using _ItOfNodes = list<_Node>::iterator;

    int _capacity{0};
    int _size{0};
    map<string, _ItOfNodes> _mappingTable;
    list<_Node> _nodes;
    void _makeRecent(_ItOfNodes it);

public:
    explicit LRUCache(int capacity ) : _capacity{capacity} {}
    void update(const string& key, int value);
    int get(const string& key);
    void remove(const string& key);
    void insert(const string& key, int value);
    void print();
};

void LRUCache::_makeRecent(list<_Node>::iterator it) {
    // Move the node pointed by the iterator to the end of the list.
    auto node = std::move(*it);
    _nodes.erase(it);
    _nodes.push_back(std::move(node));
    auto newIterator = --(_nodes.end());
    string key = it->first;
    _mappingTable.at( key ) = newIterator;
}

void LRUCache::update( const string& key, int value ) {
    // update the value for the key and move the node to the end of the list.
    auto it = _mappingTable.at(key);
    it->second = value;
    _makeRecent(it);
}

int LRUCache::get( const string& key ) {
    // move the node corresponding to the key to the end of the list.
    // and return the value for the key.
    auto it = _mappingTable.at(key);
    auto value = it->second;
    _makeRecent(it);
    return value;
}

void LRUCache::remove(const string& key) {
    auto it = _mappingTable.at(key);
    _mappingTable.erase(key);
    _nodes.erase(it);
    --_size;
}

void LRUCache::insert(const string& key, int value) {
    if ( _mappingTable.find( key ) != _mappingTable.end() ) {
        // if the key exists, we just update the value for the key.
        update(key, value);
    }
    else {
        if ( _size < _capacity ) {
            _nodes.push_back( make_pair(key, value) );
            auto it = _nodes.end();
            --it;
            _mappingTable[ key ] = it;
            ++_size;
        }
        else {
            auto firstNode = _nodes.front();
            auto keyOfFirstNode = firstNode.first;
            remove(keyOfFirstNode);
            insert(key, value);
        }
    }
}


void LRUCache::print() {
    bool isFirst = true;
    for (const auto& node : _nodes) {
        if (!isFirst) { cout << " -> " << flush; }
        cout << "(" << node.second << "," << node.first << ")" << flush;
        isFirst = false;
    }

    cout << " | " << flush;
    cout << "size of cache: " << _size << " | "<< flush;
    cout << "size of map: " << _mappingTable.size() << flush;
    cout << endl << endl;
}


int main() {

    LRUCache c{3};

    cout << "create 3 keys" << endl;
    c.insert("A", 1);
    c.insert("B", 2);
    c.insert("C", 3);
    c.print();

    cout << "get A. A should be moved to the end of the list. " << c.get("A") << endl;
    c.print();

    cout << "insert D. B should be removed." << endl;
    c.insert("D", 4);
    c.print();

    cout << "update C" << endl;
    c.update("C", 20);
    c.print();

    cout << "remove D" << endl;
    c.remove("D");
    c.print();

    cout << "finished" << endl;
    return 0;
}

} // end of namespace
