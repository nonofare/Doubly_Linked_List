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

		// Method purpose: Return list size
		// Arguments: None
		// Returns: List size
		// Time complexity: Theta = 1
		// Comment:
		size_t get_size() {
			return size;
		}

		// Method purpose: Check if list is empty
		// Arguments: None
		// Returns: True when list has no nodes
		// Time complexity: Theta = 1
		// Comment:
		bool is_empty() {
			return size == 0;
		}

		// Method purpose: Add a new element
		// Arguments: Data (T) of a new node
		// Returns: None
		// Time complexity: Theta = 1
		// Comment:
		void push(T data) {
			push_back(data);
		}

		// (2b)
		// Method purpose: Add a new element at the begining of the list
		// Arguments: Data (T) of a new node
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

		// (2a)
		// Method purpose: Add new element at the end of the list
		// Arguments: Data (T) of a new node
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

		// (2d)
		// Method purpose: Remove first element from the list
		// Arguments: None
		// Returns: None
		// Time complexity: Theta = 1
		// Comment:
		void pop_front() {
			if (size == 0) {
				throw std::runtime_error("List is empty");
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
		}

		// (2c)
		// Method purpose: Remove last element from the list
		// Arguments: None
		// Returns: None
		// Time complexity: Theta = 1
		// Comment:
		void pop_back() {
			if (size == 0) {
				throw std::runtime_error("List is empty");
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
		}

		// (2e)
		// Method purpose: Get a node data by its index
		// Arguments: Wanted node index counted from the begining
		// Returns: Wanted node data (T)
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

		// (2f)
		// Method purpose: Set a node data by its index
		// Arguments: Wanted node index counted from the begining
		// Returns: None
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

		// (2g)
		// Method purpose: Find a node by its data
		// Arguments: Wanted node data
		// Returns: Pointer to a wanted node
		// Time complexity: O = n
		// Comment:
		Node<T>* find(T data) {
			Node<T>* current = head;

			while (current != nullptr) {
				if (current->data == data) {
					return current;
				}
				current = current->next;
			}

			return nullptr;
		}

		// (2h)
		// Method purpose: Find a node by its data and delete it
		// Arguments: Wanted node data
		// Returns: None
		// Time complexity: O = n
		// Comment:
		void remove(T data) {
			Node<T>* current = head;

			while (current != nullptr) {
				if (current->data == data) {
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

					return;
				}

				current = current->next;
			}

			throw std::runtime_error("Node not found");
		}

		// (2i)
		// Method purpose:
		// Arguments:
		// Returns:
		// Time complexity:
		// Comment:
		void order_push() {

		}

		// (2j)
		// Method purpose: Delete all list elements
		// Arguments: None
		// Returns: None
		// Time complexity: Theta = n
		// Comment:
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

		// (2k)
		// Method purpose: Return string representation of n nodes (or every node when no arguments)
		// Arguments: Quantity of nodes
		// Returns: String representation of n nodes
		// Time complexity: Theta = n
		// Comment:
		std::string to_string(size_t quantity = size) {
			if (quantity > size) {
				throw std::out_of_range("Index is out of range");
			}
			else {
				Node<T>* current = head;
				std::string text;

				for (size_t i = 0; i < quantity; i++) {
					text += std::to_string(current->data);
					text += " ";
					current = current->next;
				}

				return text;
			}
		}
	};
}