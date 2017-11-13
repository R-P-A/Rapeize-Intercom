/** 
 *	@author  Rafael Pintar Alevato
 *	@date    11/11/2017
 *	@version 1.0 
 *	
 *	@brief User class.
 *
 */

#ifndef USER
#define USER

#include <iostream>
#include "model.h"

class User : public Model{
	private:
		string name;

		string phone;

		string email;

		/**
		 *	The allowed period must be in the following format "W,W,hh:mm,hh:mm,".
		 *	The CSV values means: first week day (0-6), last week day (0-6), first hour:min, last hour:min.
		 */
		string allowedPeriod;

	public:
		/**
		 *	Constructor that set all variables to "".
		 */
		User();

		/**
		 *	Constructor that set all variables to the values given.
		 *	The allowed period must be in the following format "W,W,hh:mm,hh:mm,".
		 *	The CSV values means: first week day (0-6), last week day (0-6), first hour:min, last hour:min.
		 *	@param idInput The value to set the id.
		 *	@param nameInput The value to set the name.
		 *	@param phoneInput The value to set the phone.
		 *	@param emailInput The value to set the email.
		 *	@param allowedPeriodInput The value to set the allowedPeriod.
		 *	@throw const char* "Allowed period in wrong format".
		 */
		User(unsigned long int idInput, string nameInput, string phoneInput, string emailInput, string allowedPeriodInput);

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
		 *	Get the allowed period in the following format "W,W,hh:mm,hh:mm,".
		 *	The CSV values means: first week day (0-6), last week day (0-6), first hour:min, last hour:min.
		 *	@return The Allowed Period.
		 */
		string getAllowedPeriod();

		/**
		 *	Set the allowed period in the following format "W,W,hh:mm,hh:mm,".
		 *	The CSV values means: first week day (0-6), last week day (0-6), first hour:min, last hour:min.
		 *	@param value The value to set the Allowed Period.
		 *	@throw const char* "Wrong format".
		 */
		void setAllowedPeriod(string value);
};

#endif	// USER