#include "DataContainer.h"
#include "../Value/Value.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace messaging
		{
			bool DataContainer::Empty() const
			{
				return values_.empty();
			}

			bool DataContainer::HasValue(const std::string& key) const
			{
				for (size_t i = 0; i < values_.size(); i++)
				{
					if (values_[i].first == key)
					{
						return true;
					}
				}

				return false;
			}

			void DataContainer::SetValue(const std::string& key, const Value& value)
			{
				for (size_t i = 0; i < values_.size(); i++)
				{
					if (values_[i].first == key)
					{
						values_[i].second = value;
						return;
					}
				}

				values_.emplace_back(key, value);
			}

			Value& DataContainer::GetValue(const std::string& key)
			{
				return const_cast<Value&>(const_cast<const DataContainer*>(this)->GetValue(key));
			}

			const Value& DataContainer::GetValue(const std::string& key) const
			{
				auto ptr = FindValue(key);
				JUNJINJEN_ASSERT(ptr != nullptr);
				return *ptr;
			}

			Value& DataContainer::operator[](const std::string& key)
			{
				auto ptr = FindValue(key);
				if (ptr != nullptr)
				{
					return *ptr;
				}

				values_.emplace_back(key, Value());
				return values_.back().second;
			}

			void DataContainer::operator=(const DataContainer& other)
			{
				values_ = other.values_;
			}

			void DataContainer::operator=(DataContainer&& other) noexcept
			{
				values_ = std::move(other.values_);
			}

			bool DataContainer::operator==(const DataContainer& other) const
			{
				return values_ == other.values_;
			}

			void DataContainer::SetInt32(const std::string& key, int32_t value)
			{
				auto node = FindValue(key);
				if (node != nullptr)
				{
					node->SetInt32(value);
				}
				else
				{
					values_.emplace_back(key, Value(value));
				}
			}

			void DataContainer::SetInt64(const std::string& key, int64_t value)
			{
				auto node = FindValue(key);
				if (node != nullptr)
				{
					node->SetInt64(value);
				}
				else
				{
					values_.emplace_back(key, Value(value));
				}
			}

			void DataContainer::SetBoolean(const std::string& key, bool value)
			{
				auto node = FindValue(key);
				if (node != nullptr)
				{
					node->SetBoolean(value);
				}
				else
				{
					values_.emplace_back(key, Value(value));
				}
			}

			void DataContainer::SetString(const std::string& key, const std::string& value)
			{
				auto node = FindValue(key);
				if (node != nullptr)
				{
					node->SetString(value);
				}
				else
				{
					values_.emplace_back(key, Value(value));
				}
			}

			void DataContainer::SetString(const std::string& key, std::string&& value)
			{
				auto node = FindValue(key);
				if (node != nullptr)
				{
					node->SetString(std::move(value));
				}
				else
				{
					values_.emplace_back(key, Value(std::move(value)));
				}
			}

			void DataContainer::SetByteString(const std::string& key, const byte_string& value)
			{
				auto node = FindValue(key);
				if (node != nullptr)
				{
					node->SetByteString(value);
				}
				else
				{
					values_.emplace_back(key, Value(value));
				}
			}

			void DataContainer::SetByteString(const std::string& key, byte_string&& value)
			{
				auto node = FindValue(key);
				if (node != nullptr)
				{
					node->SetByteString(std::move(value));
				}
				else
				{
					values_.emplace_back(key, Value(std::move(value)));
				}
			}

			void DataContainer::SetFloat(const std::string& key, float value)
			{
				auto node = FindValue(key);
				if (node != nullptr)
				{
					node->SetFloat(value);
				}
				else
				{
					values_.emplace_back(key, Value(value));
				}
			}

			void DataContainer::SetDouble(const std::string& key, double value)
			{
				auto node = FindValue(key);
				if (node != nullptr)
				{
					node->SetDouble(value);
				}
				else
				{
					values_.emplace_back(key, Value(value));
				}
			}

			int32_t DataContainer::GetInt32(const std::string& key) const
			{
				auto node = FindValue(key);
				JUNJINJEN_ASSERT(node != nullptr);
				return node->AsInt32();
			}

			int64_t DataContainer::GetInt64(const std::string& key) const
			{
				auto node = FindValue(key);
				JUNJINJEN_ASSERT(node != nullptr);
				return node->AsInt64();
			}

			bool DataContainer::GetBoolean(const std::string& key) const
			{
				auto node = FindValue(key);
				JUNJINJEN_ASSERT(node != nullptr);
				return node->AsBoolean();
			}

			const std::string& DataContainer::GetString(const std::string& key) const
			{
				auto node = FindValue(key);
				JUNJINJEN_ASSERT(node != nullptr);
				return node->AsString();
			}

			const byte_string& DataContainer::GetByteString(const std::string& key) const
			{
				auto node = FindValue(key);
				JUNJINJEN_ASSERT(node != nullptr);
				return node->AsByteString();
			}

			float DataContainer::GetFloat(const std::string& key) const
			{
				auto node = FindValue(key);
				JUNJINJEN_ASSERT(node != nullptr);
				return node->AsFloat();
			}

			double DataContainer::GetDouble(const std::string& key) const
			{
				auto node = FindValue(key);
				JUNJINJEN_ASSERT(node != nullptr);
				return node->AsDouble();
			}

			DataContainer& DataContainer::SetContainer(const std::string& key)
			{
				auto node = FindValue(key);
				if (node != nullptr)
				{
					return node->CreateContainer();
				}
				else
				{
					values_.emplace_back(key, Value());
					return values_.back().second.CreateContainer();
				}
			}

			void DataContainer::SetContainer(const std::string& key, const DataContainer& value)
			{
				auto node = FindValue(key);
				if (node != nullptr)
				{
					node->CreateContainer(value);
				}
				else
				{
					values_.emplace_back(key, Value(value));
				}
			}

			void DataContainer::SetContainer(const std::string& key, DataContainer&& value)
			{
				auto node = FindValue(key);
				if (node != nullptr)
				{
					node->CreateContainer(std::move(value));
				}
				else
				{
					values_.emplace_back(key, Value(std::move(value)));
				}
			}

			const DataContainer& DataContainer::GetContainer(const std::string& key) const
			{
				auto node = FindValue(key);
				JUNJINJEN_ASSERT(node != nullptr);
				return node->AsContainer();
			}

			DataContainer& DataContainer::GetContainer(const std::string& key)
			{
				return const_cast<DataContainer&>(const_cast<const DataContainer*>(this)->GetContainer(key));
			}

			std::vector<Value>& DataContainer::SetArray(const std::string& key)
			{
				auto node = FindValue(key);
				if (node != nullptr)
				{
					return node->CreateArray();
				}
				else
				{
					values_.emplace_back(key, Value());
					return values_.back().second.CreateArray();
				}
			}

			void DataContainer::SetArray(const std::string& key, const std::vector<Value>& value)
			{
				auto node = FindValue(key);
				if (node != nullptr)
				{
					node->CreateArray(value);
				}
				else
				{
					values_.emplace_back(key, Value(value));
				}
			}

			void DataContainer::SetArray(const std::string& key, std::vector<Value>&& value)
			{
				auto node = FindValue(key);
				if (node != nullptr)
				{
					node->CreateArray(std::move(value));
				}
				else
				{
					values_.emplace_back(key, Value(std::move(value)));
				}
			}

			const std::vector<Value>& DataContainer::GetArray(const std::string& key) const
			{
				auto node = FindValue(key);
				JUNJINJEN_ASSERT(node != nullptr);
				return node->AsArray();
			}

			std::vector<Value>& DataContainer::GetArray(const std::string& key)
			{
				return const_cast<std::vector<Value>&>(const_cast<const DataContainer*>(this)->GetArray(key));
			}

			std::vector<std::pair<std::string, Value>>::iterator DataContainer::begin()
			{
				return values_.begin();
			}

			std::vector<std::pair<std::string, Value>>::iterator DataContainer::end()
			{
				return values_.end();
			}

			std::vector<std::pair<std::string, Value>>::const_iterator DataContainer::cbegin() const
			{
				return values_.cbegin();
			}

			std::vector<std::pair<std::string, Value>>::const_iterator DataContainer::cend() const
			{
				return values_.cend();
			}

			inline const Value* DataContainer::FindValue(const std::string& key) const
			{
				for (size_t i = 0; i < values_.size(); i++)
				{
					if (values_[i].first == key)
					{
						return &values_[i].second;
					}
				}

				return nullptr;
			}

			inline Value* DataContainer::FindValue(const std::string& key)
			{
				return const_cast<Value*>(const_cast<const DataContainer*>(this)->FindValue(key));
			}
		}
	}
}
