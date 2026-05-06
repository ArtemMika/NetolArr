#include <iostream>
#include <catch2/catch_test_macros.hpp>

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};

//Список пуст
TEST_CASE("List is empty when created", "[Empty]") 
{
    List list;
    REQUIRE(list.Empty() == true);  // список пуст после создания
}

TEST_CASE("List is not empty after adding elements", "[Empty]") 
{
    List list;
    list.PushFront(1);  // добавляем элемент
    REQUIRE(list.Empty() == false);  // список не пуст
}

//Проверяем корректность подсчёта элементов :
TEST_CASE("Size of empty list is 0", "[Size]")
{
    List list;
    REQUIRE(list.Size() == 0);  // размер пустого списка = 0
}

TEST_CASE("Size increases with added elements", "[Size]") 
{
    List list;
    list.PushFront(1);
    REQUIRE(list.Size() == 1);
    list.PushBack(2);
    REQUIRE(list.Size() == 2);
}

TEST_CASE("Size decreases with removed elements", "[Size]") 
{
    List list;
    list.PushFront(1);
    list.PushBack(2);
    list.PopFront();  // удаляем первый элемент
    REQUIRE(list.Size() == 1);
}

//Проверяем очистку списка и обработку крайних случаев :
TEST_CASE("Clear() makes list empty and size = 0", "[Clear]") 
{
    List list;
    list.PushFront(1);
    list.PushBack(2);
    REQUIRE(list.Size() == 2);  // список содержит 2 элемента

    list.Clear();  // очищаем список
    REQUIRE(list.Empty() == true);  // список пуст
    REQUIRE(list.Size() == 0);  // размер = 0
}

TEST_CASE("Clear() on empty list is safe", "[Clear]") 
{
    List list;
    list.Clear();  // очищаем пустой список
    REQUIRE(list.Empty() == true);  // остаётся пустым
    REQUIRE(list.Size() == 0);  // размер остаётся 0
}