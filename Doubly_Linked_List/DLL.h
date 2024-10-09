#include <string>

namespace DLL {

	template <typename T>
	class DoubLinList {

		template <typename T>
		class Node {
			friend DoubLinList;

			T data;
			Node<T>* next;
			Node<T>* prev;

			Node(T data) {
				this->data = data;
				next = nullptr;
				prev = nullptr;
			}
		};

		size_t size;
		Node<T>* head;
		Node<T>* tail;

	public:
		DoubLinList() {
			size = 0;
			head = nullptr;
			tail = nullptr;
		}

		~DoubLinList() {
			erase();
		}

		// Method purpose: To get list element count
		// Arguments: None
		// Returns: List size
		// Time complexity: Theta = 1
		// Comment:
		size_t get_size() {
			return size;
		}

		// Method purpose: To check if list is has no elements
		// Arguments: None
		// Returns: True when list has no elements
		// Time complexity: Theta = 1
		// Comment:
		bool is_empty() {
			return size == 0;
		}

		// Method purpose: To add a new element
		// Arguments: Data(T) of a new element
		// Returns: None
		// Time complexity: Theta = 1
		// Comment:
		void push(T data) {
			push_back(data);
		}

		// Method purpose: To add a new element at the front of the list
		// Arguments: Data(T) of a new element
		// Returns: None
		// Time complexity: Theta = 1
		// Comment:
		void push_front(T data) {
			Node<T>* newNode = new Node<T>(data);

			if (size > 0) {
				head->prev = newNode;
				newNode->next = head;
				head = newNode;
			}
			else {
				head = newNode;
				tail = newNode;
			}

			size++;
		}

		// Method purpose: To add new element at the back of the list
		// Arguments: Data(T) of a new element
		// Returns: None
		// Time complexity: Theta = 1
		// Comment:
		void push_back(T data) {
			Node<T>* newNode = new Node<T>(data);

			if (size > 0) {
				tail->next = newNode;
				newNode->prev = tail;
				tail = newNode;
			}
			else {
				head = newNode;
				tail = newNode;
			}

			size++;
		}

		// Method purpose: To remove oldest list element
		// Arguments: None
		// Returns: True when element was found and deleted
		// Time complexity: Theta = 1
		// Comment:
		bool pop_front() {
			if (size == 0) {
				return false;
			}
			else if (size > 1) {
				Node<T>* temp = head->next;
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

		// Method purpose: To remove youngest list element
		// Arguments: None
		// Returns: True when element was found and deleted
		// Time complexity: Theta = 1
		// Comment:
		bool pop_back() {
			if (size == 0) {
				return false;
			}
			else if (size > 1) {
				Node<T>* temp = tail->prev;
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

		// Method purpose:
		// Arguments:
		// Returns:
		// Time complexity: O = n/2
		// Comment:
		const T& operator[](size_t index) const {
			if (index > size - 1) {
				throw std::out_of_range("Index is out of range");
			}
			else {
				Node<T>* temp;

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

		// Method purpose:
		// Arguments:
		// Returns:
		// Time complexity: O = n/2
		// Comment:
		T& operator[](size_t index) {
			if (index > size - 1) {
				throw std::out_of_range("Index is out of range");
			}
			else {
				Node<T>* temp;

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

		// Method purpose:
		// Arguments:
		// Returns:
		// Time complexity: O = n
		// Comment:
		Node<T>* find(T pattern, bool(*cmp)(T, T)) {
			Node<T>* current = head;

			while (current != nullptr) {
				if (cmp(current->pattern, pattern)) {
					return current;
				}
				current = current->next;
			}

			return nullptr;
		}

		// Method purpose:
		// Arguments:
		// Returns:
		// Time complexity: O = n
		// Comment:
		bool remove(T pattern, bool(*cmp)(T, T)) {
			Node<T>* current = head;

			while (current != nullptr) {
				if (cmp(current->data, pattern)) {
					if (current == head) {
						pop_front();
					}
					else if (current == tail) {
						pop_back();
					}
					else {
						Node<T>* prev = current->prev;
						Node<T>* next = current->next;

						prev->next = next;
						next->prev = prev;

						delete current;
						size--;
					}

					return true;
				}

				current = current->next;
			}

			return false;
		}

		// Method purpose:
		// Arguments:
		// Returns:
		// Time complexity:
		// Comment:
		void order_push() {

		}

		// Method purpose: To delete all list elements
		// Arguments: None
		// Returns: None
		// Time complexity: Theta = n
		// Comment:
		void erase() {
			Node<T>* temp;

			while (tail != nullptr) {
				temp = tail->prev;
				delete tail->data;
				delete tail;
				tail = temp;
			}

			head = nullptr;
			size = 0;
		}

		// Method purpose:
		// Arguments:
		// Returns:
		// Time complexity: Theta = n
		// Comment:
		std::string to_str(std::string(*out_to_string)(T) = nullptr) {
			Node<T>* temp = head;
			std::string text;

			text = "List has: " + std::to_string(int(size)) + " elements ";
			if (out_to_string != nullptr) {
				for (size_t i = 0; i < size; i++) {
					text += out_to_string(temp->data);
					text += " ";
					temp = temp->next;
				}
			}
			else {
				for (size_t i = 0; i < size; i++) {
					//text += std::to_string(temp->data);
					text += " ";
					temp = temp->next;
				}
			}

			return text;
		}
	};
}