namespace DLL {
	
	template <typename T>
	class List {
		size_t size;
		ListNode<T>* head;
		ListNode<T>* tail;

	public:
		List<T> List<T>() {
			size = 0;
		}

		void add_at_head(T data) {
			ListNode<T>* node = new ListNode<T>(data);
			if (size > 0) {
				head->prev = node;
				node->next = head;
				head = node;
			}
			else {
				head = node;
				tail = node;
			}
			size++;
		}

		void add_at_tail(T data) {
			ListNode<T>* node = new ListNode<T>(data);
			if (size > 0) {
				tail->next = node;
				node->prev = tail;
				tail = node;
			}
			else {
				head = node;
				tail = node;
			}
			size++;
		}
	};

	template <typename T>
	class ListNode {
		T data;
		ListNode<T>* next;
		ListNode<T>* prev;

	public:
		ListNode<T> ListNode<T>(T data) {
			this.data = data;
		}
	};
}