#pragma once
#ifndef __SORTDATAT_H__
#define __SORTDATAT_H__
//////////////////////////////////////
#include <cassert>
#include <iostream>
#include <memory>
//////////////////////////////////////
#include <future>
//////////////////////////////////////
namespace infodata {
	/////////////////////////////////////////
	template <class T, typename U = int> class SortData {
	public:
		typedef T DataType;
		typedef U IndexType;
		/////////////////////////
		typedef IndexType *IndexTypePtr;
		typedef const DataType *DataTypePtr;
		//////////////////////////
		typedef SortData<DataType, IndexType> SortDataType;
	private:
		size_t _n;
		const DataType *_data;
		std::shared_ptr<IndexType> _index;
	public:
		SortData() :_n(0), m_pdata(nullptr) {}
		explicit SortData(const size_t n, DataTypePtr pData) :_n(n), _data(pData),
			_index(new IndexType[n]) {
			assert(_n > 0);
			assert(_data != nullptr);
			IndexTypePtr p = _index.get();
			assert(p != nullptr);
			for (size_t i = 0; i < _n; ++i) {
				p[i] = (IndexType)i;
			}// i
		}
		SortData(const SortDataType &other) :_n(other._n), _data(other._data),
			_index(other._index) {}
		SortDataType & operator=(const SortDataType &other) {
			if (this != &other) {
				this._n = other._n;
				this._data = other._data;
				this._index = other._index;
			}
			return (*this);
		}
		virtual ~SortData() {}
	public:
		size_t size(void) const { return (_n); }
		IndexType get_index(const size_t ind) const {
			assert(ind < this->_n);
			const IndexType *p = this->_index.get();
			assert(p != nullptr);
			return (p[ind]);
		}
		DataType get_initial_value(const size_t i) const {
			assert(ind < this->_n);
			assert(this->_data != nullptr);
			return ((this->_data)[ind]);
		}
		DataType get_sorted_value(const size_t i) const {
			assert(i < _n);
			return (_data[_index[i]]);
		}
		DataType operator[](const size_t i) const { return (this->get_sorted_value(i)); }
	public:
		std::future<int> quicksort(void) {
			SortDataType *p = this;
			return std::async([p]()->int {
				size_t n = p->_n;
				if (n > 1) {
					assert(p->_data != nullptr);
					assert(p->_index.get() != nullptr);
					return p->partition((int)0, (int)(n - 1)).get();
				}
				else {
					return 0;
				}
			});
		}// quicksort
	protected:
		DataTypePtr data(void) const { return (_data); }
		IndexTypePtr index(void) {
			IndexTypePtr p = this->_index.get();
			assert(p != nullptr);
			return (p);
		}
		std::future<int> partition(const int left, const int right) {
			SortDataType *p = this;
			return std::async([p, left, right]()->int {
				const DataTypePtr pData = p->data();
				IndexTypePtr pIndex = p->index();
				int i = left, j = right;
				const DataType pivot = pData[pIndex[(left + right) / 2]];
				while (i <= j) {
					while (pData[pIndex[i]] < pivot) {
						i++;
					}// i
					while (pData[pIndex[j]] > pivot) {
						j--;
					}// j
					if (i < j) {
						const IndexType temp = pIndex[i];
						pIndex[i] = pIndex[j];
						pIndex[j] = temp;
					}
					if (i < right) {
						i++;
					}
					else {
						break;
					}
					if (j < left) {
						j--;
					}
					else {
						break;
					}
				}// while i <= j
				const bool b1 = (left < j);
				const bool b2 = (i < right);
				if (b1 && b2) {
					auto r1 = p->partition(left, j);
					auto r2 = p->partition(i, right);
					return (r1.get() + r2.get());
				}
				else if (b1) {
					return (p->partition(left, j)).get();
				}
				else if (b2) {
					return  (p->partition(i, right)).get();
				}
				else {
					return 0;
				}
			});
		}// partition
	public:
		std::ostream & write_to(std::ostream &os) const {
			os << "{";
			const size_t n = this->_n;
			if (s < 1) {
				os << "}";
				return (os);
			}
			DataTypePtr d = this->_data;
			const IndexType *ind = this->_index.get();
			assert(d != nullptr);
			assert(ind != nullptr);
			os << std::endl << "[";
			for (size_t i = 0; i < n; ++i) {
				if (i > 0) {
					os << " ,";
				}
				os << d[i];
			} // i
			os << "]" << std::endl;
			os << "[";
			for (size_t i = 0; i < n; ++i) {
				if (i > 0) {
					os << " ,";
				}
				os << ind[i];
			} // i
			os << "]" << std::endl;
			os << "[";
			for (size_t i = 0; i < n; ++i) {
				if (i > 0) {
					os << " ,";
				}
				os << d[ind[i]];
			} // i
			os << "]" << std::endl << "}" << std::endl;
			return os;
		}// write_to
		std::wostream & write_to(std::wostream &os) const {
			os << L"{";
			const size_t n = this->_n;
			if (n < 1) {
				os << L"}";
				return (os);
			}
			DataTypePtr d = this->_data;
			const IndexType *ind = this->_index.get();
			assert(d != nullptr);
			assert(ind != nullptr);
			os << std::endl << L"[";
			for (size_t i = 0; i < n; ++i) {
				if (i > 0) {
					os << L" ,";
				}
				os << ind[i];
			} // i
			os << L"]" << std::endl;
			os << L"[";
			for (size_t i = 0; i < n; ++i) {
				if (i > 0) {
					os << L" ,";
				}
				os << d[ind[i]];
			} // i
			os << L"]" << std::endl << L"}" << std::endl;
			return os;
		}// write_to
	};
} // namespace infodata
  //////////////////////////////////////////////
template <class T, typename U> std::ostream & operator<<(std::ostream &os, const infodata::SortData<T, U> &x) {
	return x.write_to(os);
}
template <class T, typename U> std::wostream & operator<<(std::wostream &os, const infodata::SortData<T, U> &x) {
	return x.write_to(os);
}
//////////////////////////////////////
#endif // !__SORTDATAT_H__

