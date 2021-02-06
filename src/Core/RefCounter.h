// 学学学
#pragma once

#ifndef _REFCOUNTER_H_
#define _REFCOUNTER_H_

class RefCounter
{
public:
	static constexpr uint16_t kDestroyedCounterValue = std::numeric_limits<uint16_t>::max();

	RefCounter() = default;
	virtual ~RefCounter() = default;
private:
	friend void intrusive_ptr_add_ref(RefCounter* p) noexcept
	{
		if (p->_counter == kDestroyedCounterValue)
		{
			return;
		}
		p->_counter++;
	}

	friend void intrusive_ptr_release(RefCounter* p) noexcept
	{
		if (p->_counter == 0)
		{
			return;
		}

		void* memoryToRelease = nullptr;

		{
			// Нельзя повторно удалять уже удалённый объект
			if (p->_counter == 0 || p->_counter == kDestroyedCounterValue)
			{
				return;
			}

			if (--p->_counter != 0)
			{
				return;
			}

			// В деструкторе объекта значение счётчика будет иметь специальное значение
			p->_counter = kDestroyedCounterValue;

			// Если нет слабых ссылок на объект, то весь объект можно удалять
			if (p->_counter_weak == 0)
			{
				p->_counter_weak = kDestroyedCounterValue;
			}
			else
			{
				// Частичное удаление.
				// Увеличим счётчик слабых ссылок
				p->_counter_weak++;
				// Находим указатель на начало объекта (p может указывать в середину объекта при множественном наследовании).
				memoryToRelease = dynamic_cast<void*>(p);
				// В деструкторе может выполняться блокировка
				// Вызываем деструктор (виртуальный), но не освобождаем память, т.к. она ещё используется под счётчик weak_ptr.
				p->~RefCounter();

				// уменьшаем счётчик слабых ссылок и если они ещё остались - оставляем память выделенной
				if (--p->_counter_weak != 0)
				{
					// Записываем указатель вместо vptr (всё равно он уже уничтожен).
					*reinterpret_cast<void**>(p) = memoryToRelease;
					return;
				}
			}
		}

		if (memoryToRelease == nullptr)
		{
			delete p;
		}
		else
		{
			::operator delete(memoryToRelease);
		}
	}

	uint16_t _counter = 0;
	uint16_t _counter_weak = 0;
};

#endif // !_ASSET_H_