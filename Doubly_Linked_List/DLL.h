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

		void Push(T data) {
			try {
				PushBack(data);
			}
			catch (const std::exception& ex) {
				throw std::runtime_error("DLL::Push() -> " + std::string(ex.what()));
			}
		}

		void PushFront(T data) {
			Node* node = nullptr;
			try {
				node = new Node(data);
			}
			catch (const std::bad_alloc& ex) {
				throw std::runtime_error("DLL::PushFront() -> " + std::string(ex.what()));
			}

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
			Node* node = nullptr;
			try {
				node = new Node(data);
			}
			catch (const std::bad_alloc& ex) {
				throw std::runtime_error("DLL::PushBack() -> " + std::string(ex.what()));
			}

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

		void OrderPush(T data, bool(*cmp_equal)(T, T) = nullptr) {
			Node* node = nullptr;
			try {
				node = new Node(data);
			}
			catch (const std::bad_alloc& ex) {
				throw std::runtime_error("DLL::OrderPush() -> " + std::string(ex.what()));
			}

			if (size == 0) {
				head = node;
				tail = node;
			}
			else {
				Node* current = head;
				Node* temp = head;

				while (current) {
					if (cmp_equal) {
						if (cmp_equal(node->data, current->data) && cmp_equal(current->data, temp->data)) {
							temp = current;
						}
					}
					else if constexpr (std::is_arithmetic_v<T>) {
						if (node->data == current->data && current->data == temp->data) {
							temp = current;
						}
					}
					else {
						throw std::runtime_error("T was not arithmetic and no cmp was provided");
					}

					current = current->next;
				}
				if (temp == head) {
					try {
						PushFront(data);
					}
					catch (const std::exception& ex) {
						throw std::runtime_error("DLL::OrderPush() -> " + std::string(ex.what()));
					}
					delete node;
				}
				else if (temp == tail) {
					try {
						PushBack(data);
					}
					catch (const std::exception& ex) {
						throw std::runtime_error("DLL::OrderPush() -> " + std::string(ex.what()));
					}
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
		}

		void Pop() {
			try {
				PopFront();
			}
			catch (const std::exception& ex) {
				throw std::runtime_error("DLL::Pop() -> " + std::string(ex.what()));
			}
		}

		void PopFront() {
			if (!size) { throw std::length_error("DLL::PopFront(): list was empty"); }

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
		}

		void PopBack() {
			if (!size) { throw std::length_error("DLL::PopBack(): list was empty"); }

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
		}

		bool Remove(T data, bool(*cmp_equal)(T, T) = nullptr) {
			Node* temp = nullptr;
			try {
				temp = Find(data, cmp_equal);
			}
			catch (const std::exception& ex) {
				throw std::runtime_error("DLL::Remove() -> " + std::string(ex.what()));
			}

			if (temp) {
				if (temp == head) {
					try {
						PopFront();
					}
					catch (const std::exception& ex) {
						throw std::runtime_error("DLL::Remove() -> " + std::string(ex.what()));
					}
				}
				else if (temp == tail) {
					try {
						PopBack();
					}
					catch (const std::exception& ex) {
						throw std::runtime_error("DLL::Remove() -> " + std::string(ex.what()));
					}
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

		Node* Find(T data, bool(*cmp_equal)(T, T) = nullptr) const {
			Node* current = head;

			while (current != nullptr) {
				if (cmp_equal) {
					if (cmp_equal(current->data, data)) {
						return current;
					}
				}
				else if constexpr (std::is_arithmetic_v<T>) {
					if (current->data == data) {
						return current;
					}
				}
				else {
					throw std::runtime_error("T was not arithmetic and no cmp was provided");
				}

				current = current->next;
			}

			return nullptr;
		}

		T& operator[](size_t index) {
			if (index >= size) { throw std::out_of_range("DLL::Operator[]: index (" + std::to_string(index) + ") was greater or equal to list size (" + std::to_string(int(size)) + ")"); }
			
			Node* temp = nullptr;

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

		const T& operator[](size_t index) const {
			if (index >= size) { throw std::out_of_range("DLL::Operator[]: index (" + std::to_string(index) + ") was greater or equal to list size (" + std::to_string(int(size)) + ")"); }

			Node* temp = nullptr;

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

		std::string ToString(unsigned int limit = 0, std::string(*cmp_string)(T) = nullptr) const {
			if (limit <= 0 || limit > size) {
				limit = size;
			}

			std::string text = "Doubly Linked List:\n";
			text += "size: " + std::to_string(int(size)) + "\n";
			text += "{\n";

			Node* temp = head;
			if (cmp_string) {
				for (size_t i = 0; i < limit; i++) {
					text += cmp_string(temp->data);
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
				text = "T is not arithmetic and no cmp was provided\n";
			}

			if (limit < size) {
				text += "[...]\n";
			}

			text += "}\n";

			return text;
		}
	};
}