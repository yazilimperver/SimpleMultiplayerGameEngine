/**
 * \file    CommunicationParameters.h
 * \date    2019/06/03
 * \author  yazilimperver
 * \brief
 * Copyright © 2018, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef COMMUNICATIONPARAMETERS_H__
#define COMMUNICATIONPARAMETERS_H__

#include <any>
#include <string>
#include <optional>
#include <unordered_map>

 /// <summary>
 /// This class is responsible for holding communication medium parameters
 /// </summary>
class CommunicationParameters
{
public:
	/// <summary>
	/// Print currently registered parameters
	/// </summary>
	void printCurrentParameters();

	/// <summary>
	/// This method update existing parameter value and add given parameter if not exist
	/// </summary>
	/// <param name="paramName">Parameter Name</param>
	/// <param name="paramValue">Parameter Value</param>
	void updateParameterValue(const std::string& paramName, const std::any& paramValue);

	/// <summary>
	/// This method check if current mapping contains given parameter name
	/// </summary>
	/// <param name="paramName">The parameter that we will check</param>
	/// <returns>true if it exist, false o.w.</returns>
	bool hasParameter(const std::string& paramName);

	/// <summary>
	/// Obtain parameter value with respect to given fiParametereld name
	/// </summary>
	/// <param name="key">Parameter Name</param>
	/// <returns>The value of parameter if exist o.w. no value is returned!</returns>
	std::optional<std::any> getParameterValue(const std::string& paramName);

	/// <summary>
	/// The template version of getParameterValue which returns the requested value as parameter to prevent any cast
	/// </summary>
	/// <param name="paramName">Parameter Name</param>
	/// <param name="paramValue">Parameter Value</param>
	/// <returns>true if parameter is found, o.w. false</returns>
	template <typename T>
	bool getParameterValue(const std::string& paramName, T& paramValue);
protected:
	/// <summary>
	/// Each parameter will be registered via a Parameter name in string as they will not affect the runtime performance
	/// Each communication medium is responsible for specific parameter
	/// </summary>
	std::unordered_map<std::string, std::any> mParameters;
};

template <typename T>
bool CommunicationParameters::getParameterValue(const std::string& paramName, T& paramValue)
{
	bool isValueExist{ false };

	if (auto itr = mParameters.find(paramName); itr != mParameters.end())
	{
		if (auto valPtr = std::any_cast<T>(&itr->second); valPtr)
		{
			paramValue = *valPtr;
			isValueExist = true;
		}
	}

	return isValueExist;
}

#endif // COMMUNICATIONPARAMETERS_H__

/*
  Copyright (c) [2018] [Yazilimperver <yazilimpervergs@gmail.com>]

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
