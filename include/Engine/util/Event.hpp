/* 
 * File:   Event.hpp
 * Author: iMer
 *
 * Created on 23. August 2014, 17:44
 */

#ifndef UTIL_EVENT_HPP
#define	UTIL_EVENT_HPP
#include <list>
namespace engine {
    namespace util {

        template<typename... T> class EventHandler {
        public:
            virtual void handle(T...)=0;
        };

        template<typename... T> class Event {
        protected:
            std::list<EventHandler<T...>*> m_callbacks;
        public:

            void AddHandler(EventHandler<T...>* handler) {
                m_callbacks.push_back(handler);
            }

            void RemoveHandler(EventHandler<T...>* handler) {
                m_callbacks.remove(handler);
            }

            void Fire(T... args) {
                for (auto it = m_callbacks.begin(); it != m_callbacks.end();) {
                    (*it++)->handle(args...);
                }
            }
        };
    }
}

#endif	/* UTIL_EVENT_HPP */
