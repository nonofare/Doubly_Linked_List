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

			~Node() {
				if constexpr (std::is_pointer_v<T>) {
					delete data;
				}
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

		// Method purpose: Get the list element count
		// Arguments: None
		// Returns: List size
		// Time complexity: Theta(1)
		size_t get_size() const {
			return size;
		}

		// Method purpose: Check if list has elements
		// Arguments: None
		// Returns: True when list has no elements, false otherwise
		// Time complexity: Theta(1)
		bool is_empty() const {
			return size == 0;
		}

		// Method purpose: Add a new element to the list
		// Arguments: Data(T) of a new element
		// Returns: None
		// Time complexity: Theta(1)
		void push(T data) {
			push_back(data);
		}

		// Method purpose: Add a new element at front of the list
		// Arguments: Data(T) of a new element
		// Returns: None
		// Time complexity: Theta(1)
		void push_front(T data) {
			Node<T>* newNode = new Node<T>(data);

			if (size == 0) {
				head = newNode;
				tail = newNode;
			}
			else {
				head->prev = newNode;
				newNode->next = head;
				head = newNode;
			}

			size++;
		}

		// Method purpose: Add a new element at back of the list
		// Arguments: Data(T) of a new element
		// Returns: None
		// Time complexity: Theta(1)
		void push_back(T data) {
			Node<T>* newNode = new Node<T>(data);

			if (size == 0) {
				head = newNode;
				tail = newNode;
			}
			else {
				tail->next = newNode;
				newNode->prev = tail;
				tail = newNode;
			}

			size++;
		}

		// Method purpose: Remove oldest list element
		// Arguments: None
		// Returns: True when element was found and deleted, false otherwise
		// Time complexity: Theta(1)
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

		// Method purpose: Remove youngest list element
		// Arguments: None
		// Returns: True when element was found and deleted, false otherwise
		// Time complexity: Theta(1)
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

		// Method purpose: Access to an element by index (read-only)
		// Arguments: Index of a wanted element
		// Returns: Const reference to the element
		// Time complexity: O(n/2)
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

		// Method purpose: Access to an element by index
		// Arguments: Index of a wanted element
		// Returns: Reference to the element
		// Time complexity: O(n/2)
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

		// Method purpose: Find specific element
		// Arguments: Wanted data(T) and pointer to a comparator function
		// Returns: Pointer to a found element or nullptr when element was not found
		// Time complexity: O(n)
		Node<T>* find(T pattern, bool(*cmp)(T, T)) {
			Node<T>* current = head;

			while (current != nullptr) {
				if (cmp(current->data, pattern)) {
					return current;
				}
				current = current->next;
			}

			return nullptr;
		}

		// Method purpose: Remove specific element
		// Arguments: Wanted data(T) and pointer to a comparator function
		// Returns: True if element was found and deleted, false otherwise
		// Time complexity: O(n)
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

		// Method purpose: Insert an element in an ordered position within the list
		// Arguments: Data (T) of the new element, pointer to a comparator function
		// Returns: None
		// Time complexity: O(n)
		void order_push(T data, bool(*cmp)(T, T)) {
			Node<T>* newNode = new Node<T>(data);

			if (size == 0) {
				head = newNode;
				tail = newNode;
			}
			else {
				Node<T>* current = head;
				Node<T>* temp = head;

				while (current != nullptr) {
					if (cmp(newNode->data, current->data) && cmp(current->data, temp->data)) {
						temp = current;
					}

					current = current->next;
				}
				if (temp == head) {
					push_front(data);
					delete newNode;
				}
				else if (temp == tail) {
					push_back(data);
					delete newNode;
				}
				else {
					newNode->next = temp->next;
					(temp->next)->prev = newNode;

					newNode->prev = temp;
					temp->next = newNode;
				}
			}

			size++;
		}

		// Method purpose: Delete all list elements
		// Arguments: None
		// Returns: None
		// Time complexity: Theta(n)
		void erase() {
			Node<T>* temp;

			while (tail != nullptr) {
				temp = tail->prev;
				delete tail;
				tail = temp;
			}

			head = nullptr;
			size = 0;
		}

		// Method purpose: String representation of a whole list
		// Arguments: specific to_string function if needed, how many elements to show
		// Returns: String representation of the list
		// Time complexity: Theta(n)
		std::string to_str(std::string(*out_to_string)(T) = nullptr, size_t element_count = 0) {
			Node<T>* temp = head;
			std::string text;

			if (element_count <= 0 || element_count > size) {
				element_count = size;
			}

			text = "List has " + std::to_string(int(size)) + " elements:\n";
			if (out_to_string != nullptr) {
				for (size_t i = 0; i < element_count; i++) {
					text += out_to_string(temp->data);
					temp = temp->next;
				}
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				for (size_t i = 0; i < element_count; i++) {
					text += std::to_string(temp->data);
					temp = temp->next;
				}
			}
			else {
				text = "Data type is not supported and no method was provided";
			}

			if (element_count < size) {
				text += "[...]\n";
			}

			return text;
		}
	};
}