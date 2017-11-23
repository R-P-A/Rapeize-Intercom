/** 
 *	@author  Rafael Pintar Alevato
 *	@date    11/11/2017
 *	@version 1.0 
 *	
 *	@brief User class that has id, name, phone, email and allowed period.
 *
 *	@section DESCRIPTION
 *	
 *	The id depends on the the other class Model. This class extends Model.
 *	The format of the user is: "id,password,isAdmin,name,phone,email,Monday,Friday,hh:mm,hh:mm".
 *
 */

#ifndef USER
#define USER

#include <iostream>
#include "model.h"

class User : public Model{
	private:
		string password;

		/**
		 *	If the user is admin (1) or not (0).
		 */
		bool isAdmin;

		string name;

		string phone;

		string email;

		/**
		 *	Beginning week day in the format of whole name (Sunday, Monday, etc..).
		 */
		string beginWeekDay;

		/**
		 *	End week day in the format of whole name (Sunday, Monday, etc..).
		 */
		string endWeekDay;

		/**
		 *	Beginning hour and minute of the day in the following format: hh:mm (Example: 08:30).
		 */
		string beginTime;

		/**
		 *	End hour and minute of the day in the following format: hh:mm (Example: 18:30).
		 */
		string endTime;

	public:
		/**
		 *	Constructor that set all variables to "".
		 */
		User();

		/**
		 *	@return The name.
		 */
		string getPassword();

		/**
		 *	@param value The value to set the name.
		 */
		void setPassword(string value);

		/**
		 *	@return Whether the user is admin.
		 */
		bool getIsAdmin();

		/**
		 *	@param value The value to set the name.
		 */
		void setIsAdmin(bool value);

		/**
		 *	@return The name.
		 */
		string getName();

		/**
		 *	@param value The value to set the name.
		 */
		void setName(string value);

		/**
		 *	@return The phone.
		 */
		string getPhone();

		/**
		 *	@param value The value to set the phone.
		 */
		void setPhone(string value);

		/**
		 *	@return The email.
		 */
		string getEmail();

		/**
		 *	@param value The value to set the email.
		 */
		void setEmail(string value);

		/**
		 *	@return Beginning week day in the format of whole name (Sunday, Monday, etc..).
		 */
		string getBeginWeekDay();

		/**
		 *	@param value The value to set the beginning week day in the format of whole name (Sunday, Monday, etc..).
		 */
		void setBeginWeekDay(string value);

		/**
		 *	@return End week day in the format of whole name (Sunday, Monday, etc..).
		 */
		string getEndWeekDay();

		/**
		 *	@param value The value to set the end week day in the format of whole name (Sunday, Monday, etc..).
		 */
		void setEndWeekDay(string value);

		/**
		 *	@return Beginning hour and minute of the day in the following format: hh:mm (Example: 08:30).
		 */
		string getBeginTime();

		/**
		 *	@param value The value of beginning hour and minute of the day in the following format: hh:mm (Example: 08:30).
		 */
		void setBeginTime(string value);

		/**
		 *	@return End hour and minute of the day in the following format: hh:mm (Example: 08:30).
		 */
		string getEndTime();

		/**
		 *	@param value The value of end hour and minute of the day in the following format: hh:mm (Example: 08:30).
		 */
		void setEndTime(string value);

		string toString();
};

#endif	// USER