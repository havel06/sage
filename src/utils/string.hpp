#pragma once

class String
{
public:	
	String() = default;
	String(const char*);
	String(String&&);
	String(const String&);
	~String();

	String& operator=(String&& other);
	String& operator=(const String& other);

	static String from_int(int);

	char& operator[](int index);
	const char& operator[](int index) const;

	void append(char);
	void append(const String&);
	void pop();
	void clear();

	bool operator==(const String& other) const;
	bool operator==(const char* other) const;
	bool empty() const { return m_length == 0; }
	int length() const { return m_length; }
	bool has_prefix(const String& other) const;
	bool has_postfix(const String& other) const;
	String substring(int start, int length) const;

	const char* data() const { return m_data; }
	char* data() { return m_data; }

	void reserve(int length);
private:
	char* m_data = nullptr;
	int m_length = 0;
	int m_capacity = 0;
};
