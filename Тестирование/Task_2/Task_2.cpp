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






// Тесты для PushFront и PushBack
TEST_CASE("PushFront and PushBack add elements correctly", "[PushFront][PushBack]") {
    List list;

    SECTION("PushFront adds to the front") {
        list.PushFront(1);
        REQUIRE(list.Size() == 1);
        REQUIRE(list.PopFront() == 1);

        list.PushFront(2);
        list.PushFront(3);
        REQUIRE(list.Size() == 2);
        REQUIRE(list.PopFront() == 3);
        REQUIRE(list.PopFront() == 2);
    }

    SECTION("PushBack adds to the back") {
        list.PushBack(1);
        REQUIRE(list.Size() == 1);
        REQUIRE(list.PopBack() == 1);

        list.PushBack(2);
        list.PushBack(3);
        REQUIRE(list.Size() == 2);
        REQUIRE(list.PopBack() == 3);
        REQUIRE(list.PopBack() == 2);
    }
}

// Тесты для PopFront и PopBack с пустым списком
TEST_CASE("PopFront and PopBack throw exception on empty list", "[PopFront][PopBack][Empty]") {
    List list;

    SECTION("PopFront on empty list") {
        REQUIRE_THROWS_AS(list.PopFront(), std::runtime_error);
    }

    SECTION("PopBack on empty list") {
        REQUIRE_THROWS_AS(list.PopBack(), std::runtime_error);
    }
}

// Тесты корректности порядка элементов
TEST_CASE("Order of elements is correct after PushFront/PushBack", "[Order]") {
    List list;
    list.PushFront(1);
    list.PushBack(2);
    list.PushFront(3);

    REQUIRE(list.PopFront() == 3);  // первый добавленный спереди
    REQUIRE(list.PopFront() == 1);  // изначально первый элемент
    REQUIRE(list.PopBack() == 2);   // элемент, добавленный в конец
}

// Сложный сценарий использования списка
TEST_CASE("Complex scenario: multiple operations", "[ComplexScenario]") {
    List list;

    // Шаг 1: заполняем список
    list.PushFront(10);
    list.PushBack(20);
    list.PushFront(5);
    list.PushBack(30);

    REQUIRE(list.Size() == 4);
    REQUIRE(list.Empty() == false);

    // Шаг 2: извлекаем элементы с обоих концов
    REQUIRE(list.PopFront() == 5);   // извлекаем первый элемент (5)
    REQUIRE(list.PopBack() == 30);   // извлекаем последний элемент (30)

    REQUIRE(list.Size() == 2);       // осталось 2 элемента

    // Шаг 3: добавляем ещё элементы
    list.PushFront(1);
    list.PushBack(99);

    REQUIRE(list.Size() == 4);       // теперь 4 элемента

    // Шаг 4: очищаем список и проверяем
    list.Clear();
    REQUIRE(list.Size() == 0);
    REQUIRE(list.Empty() == true);

    // Шаг 5: проверяем работу с пустым списком после Clear
    REQUIRE_THROWS_AS(list.PopFront(), std::runtime_error);
    REQUIRE_THROWS_AS(list.PopBack(), std::runtime_error);
}

// Тесты граничных случаев
TEST_CASE("Edge cases: single element", "[EdgeCases]") {
    List list;

    SECTION("Single element: PushFront + PopFront") {
        list.PushFront(42);
        REQUIRE(list.Size() == 1);
        REQUIRE(list.PopFront() == 42);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }

    SECTION("Single element: PushBack + PopBack") {
        list.PushBack(42);
        REQUIRE(list.Size() == 1);
        REQUIRE(list.PopBack() == 42);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }
}