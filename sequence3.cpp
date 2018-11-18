#include <cassert>
#include "sequence3.h"
#include "node1.h"
#include <algorithm>
#include <cstdlib>

//had trouble with errors I emailed you about professor, I understand my errors but did not have enough time to fix them.
namespace data_structures_assignment3 {

    sequence::sequence() {
        head_ptr = nullptr;
        tail_ptr = nullptr;
        cursor = nullptr;
        precursor = nullptr;
        many_nodes = 0;
    }

    sequence::sequence(const data_structures_assignment3::sequence &source) {
        if (source.many_nodes == 0) {
            list_clear(head_ptr);
            cursor = nullptr;
            precursor = nullptr;
            tail_ptr = nullptr;
            many_nodes = 0;
        } else {
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            many_nodes = source.many_nodes;
            node *tempPreCursor;
            int count = 0;
            for (tempPreCursor = source.head_ptr; tempPreCursor != nullptr; tempPreCursor->link()) {
                if (tempPreCursor->data() == source.precursor->data()) {
                    precursor = list_locate(head_ptr, count);
                    cursor = precursor->link();
                }
                count++;
            }
            tail_ptr = list_locate(head_ptr, many_nodes);
        }
    }

    sequence::~sequence() {
        list_clear(head_ptr);
        many_nodes = 0;
        cursor = nullptr;
        precursor = nullptr;
        tail_ptr = nullptr;
    }

    void sequence::start() {
        if (many_nodes == 0) {
            cursor = nullptr;
            precursor = nullptr;
        } else {
            cursor = head_ptr;
            precursor = nullptr;
        }
    }

    void sequence::advance() {
        if (cursor != nullptr) {
            precursor = cursor;
            cursor = cursor->link();
        }
    }

    void sequence::insert(const value_type &entry) {
        if (head_ptr == NULL) {
            list_head_insert(head_ptr, entry);
            tail_ptr = head_ptr;
            cursor = head_ptr;
            precursor = NULL;
            many_nodes += 1;
        } else if (cursor == NULL || precursor == NULL) {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            many_nodes += 1;
        } else {
            list_insert(precursor, entry);
            cursor = precursor->link();
            many_nodes += 1;
        }
    }

    void sequence::attach(const data_structures_assignment3::sequence::value_type &entry) {
        if (is_item()) {
            list_insert(cursor, entry);
            precursor = cursor;
            cursor = cursor->link();
            many_nodes++;
            tail_ptr = list_locate(head_ptr, many_nodes);
        } else {
            if (many_nodes == 0) {
                list_head_insert(head_ptr, entry);
                cursor = head_ptr;
                precursor = head_ptr;
                many_nodes++;
                tail_ptr = list_locate(head_ptr, many_nodes);
            } else {
                node *tempPtr = new node(entry);
                precursor->set_link(tempPtr);
                cursor = tempPtr;
                tail_ptr = tempPtr;
                many_nodes++;
            }
        }
    }

    void sequence::remove_current() {
        assert(is_item());
        if (cursor == head_ptr) {
            if (many_nodes == 1) {
                cursor = nullptr;
                precursor = nullptr;
            }
            else {
                precursor = cursor;
                cursor = cursor->link();
            }
            list_head_remove(head_ptr);
            many_nodes--;
        }
        else if (cursor == tail_ptr) {
            list_remove(precursor);
            many_nodes--;
            cursor = nullptr;
            tail_ptr = precursor;
        }
        else {
            cursor = cursor->link();
            list_remove(precursor);
            many_nodes--;
        }
    }

    void sequence::operator =(const sequence& source){
        many_nodes = source.many_nodes;
        list_copy(source.head_ptr, head_ptr, tail_ptr);
        node* index_src;
        index_src = source.head_ptr;
        precursor = head_ptr;

        if (source.cursor == NULL) {
            if (source.precursor == NULL) {
                cursor = NULL;
                precursor = NULL;
            }
            else{
                precursor = tail_ptr;
                cursor = NULL;
            }
        }
        else{
            if (source.precursor == NULL){
                cursor = head_ptr;
                precursor = NULL;
            }
            else{
                while (index_src != source.precursor){
                    index_src = index_src->link();
                    precursor = precursor->link();
                }
                cursor = precursor->link();}}
    }

    size_t sequence::size() const {
        return many_nodes;
    }

    bool sequence::is_item() const {
        if (cursor != nullptr) {
            return true;
        } else {
            return false;
        }
    }

    double sequence::current() const {
        return cursor->data();
    }
}
