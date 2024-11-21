#pragma once
#include <string>

namespace DLL {

	template <typename T>
	class DoubLinList {

		struct Node {
			T data;
			Node* next;
			Node* prev;

			Node(T in_data) {
				data = in_data;
				next = nullptr;
				prev = nullptr;
			}

			~Node() {
				if constexpr (std::is_pointer_v<T>) {
					delete data;
				}
			}
		};

		size_t size;
		Node* head;
		Node* tail;

	public:
		DoubLinList() {
			size = 0;
			head = nullptr;
			tail = nullptr;
		}

		~DoubLinList() {
			Erase();
		}

		size_t Size() const {
			return size;
		}

		bool IsEmpty() const {
			return size == 0;
		}

		void Push(T data) {
			PushBack(data);
		}

		void PushFront(T data) {
			Node* node = new Node(data);

			if (size == 0) {
				head = node;
				tail = node;
			}
			else {
				head->prev = node;
				node->next = head;
				head = node;
			}

			size++;
		}

		void PushBack(T data) {
			Node* node = new Node(data);

			if (size == 0) {
				head = node;
				tail = node;
			}
			else {
				tail->next = node;
				node->prev = tail;
				tail = node;
			}

			size++;
		}

		bool OrderPush(T data, bool(*cmp)(T, T) = nullptr) {
			Node* node = new Node(data);

			if (size == 0) {
				head = node;
				tail = node;
			}
			else {
				Node* current = head;
				Node* temp = head;

				while (current != nullptr) {
					if (cmp) {
						if (cmp(node->data, current->data) && cmp(current->data, temp->data)) {
							temp = current;
						}
					}
					else if constexpr (std::is_arithmetic_v<T>) {
						if (node->data == current->data && current->data == temp->data) {
							temp = current;
						}
					}
					else {
						return false;
					}

					current = current->next;
				}
				if (temp == head) {
					PushFront(data);
					delete node;
				}
				else if (temp == tail) {
					PushBack(data);
					delete node;
				}
				else {
					node->next = temp->next;
					temp->next->prev = node;

					node->prev = temp;
					temp->next = node;
				}
			}

			size++;
			return true;
		}

		bool Pop() {
			return PopFront();
		}

		bool PopFront() {
			if (size == 0) {
				return false;
			}
			else if (size > 1) {
				Node* temp = head->next;

				delete head;
				head = temp;
				head->prev = nullptr;

				size--;
			}
			else {
				delete head;
				head = tail = nullptr;

				size--;
			}

			return true;
		}

		bool PopBack() {
			if (size == 0) {
				return false;
			}
			else if (size > 1) {
				Node* temp = tail->prev;

				delete tail;
				tail = temp;
				tail->next = nullptr;

				size--;
			}
			else {
				delete tail;
				head = tail = nullptr;

				size--;
			}

			return true;
		}

		bool Remove(T data, bool(*cmp)(T, T) = nullptr) {
			Node* temp = Find(data, cmp);
			if (temp) {
				if (temp == head) {
					PopFront();
				}
				else if (temp == tail) {
					PopBack();
				}
				else {
					Node* prev = temp->prev;
					Node* next = temp->next;

					prev->next = next;
					next->prev = prev;

					delete temp;
					size--;
				}

				return true;
			}

			return false;
		}

		void Erase() {
			Node* temp;

			while (tail) {
				temp = tail->prev;
				delete tail;
				tail = temp;
			}

			head = nullptr;
			size = 0;
		}

		Node* Find(T data, bool(*cmp)(T, T) = nullptr) const {
			Node* current = head;

			while (current != nullptr) {
				if (cmp) {
					if (cmp(current->data, data)) {
						return current;
					}
				}
				else if constexpr (std::is_arithmetic_v<T>) {
					if (current->data == data) {
						return current;
					}
				}
				else {
					return nullptr;
				}

				current = current->next;
			}

			return nullptr;
		}

		const T& operator[](size_t index) const {
			if (index < 0 || index >= size) {
				throw std::out_of_range("Index is out of range");
			}
			else {
				Node* temp;

				if (index < size / 2) {
					temp = head;
					for (size_t i = 0; i < index; i++) {
						temp = temp->next;
					}
				}
				else {
					temp = tail;
					for (size_t i = size - 1; i > index; i--) {
						temp = temp->prev;
					}
				}

				return temp->data;
			}
		}

		T& operator[](size_t index) {
			if (index < 0 || index >= size) {
				throw std::out_of_range("Index is out of range");
			}
			else {
				Node* temp;

				if (index < size / 2) {
					temp = head;
					for (size_t i = 0; i < index; i++) {
						temp = temp->next;
					}
				}
				else {
					temp = tail;
					for (size_t i = size - 1; i > index; i--) {
						temp = temp->prev;
					}
				}

				return temp->data;
			}
		}	

		std::string ToString(unsigned int limit = 0, std::string(*str)(T) = nullptr) const {
			if (limit <= 0 || limit > size) {
				limit = size;
			}

			std::string text = "Doubly Linked List:\n";
			text += "Size: " + std::to_string(int(size)) + "\n";
			text += "{\n";

			Node* temp = head;
			if (str) {
				for (size_t i = 0; i < limit; i++) {
					text += str(temp->data);
					text += "\n";
					temp = temp->next;
				}
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				for (size_t i = 0; i < limit; i++) {
					text += std::to_string(temp->data);
					text += "\n";
					temp = temp->next;
				}
			}
			else {
				text = "Data type is not supported and no method was provided\n";
			}

			if (limit < size) {
				text += "[...]\n";
			}

			text += "}\n";

			return text;
		}
	};
}