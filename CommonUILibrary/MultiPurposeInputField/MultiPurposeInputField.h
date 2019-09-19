#pragma once

#include <QWidget>
#include "ui_MultiPurposeInputField.h"

/*! @brief	A QT control which can be used to obtain data either in ASCII or number or binary format. */
class MultiPurposeInputField 
	: public QWidget
{
	Q_OBJECT

public:

	/*! @brief	Types of data that are supported by this QT widget*/
	enum class InputDataType
	{
		eINPUT_DATA_TYPE_ASCII,
		eINPUT_DATA_TYPE_NUMBER,
		eINPUT_DATA_TYPE_BINARY_HEX,
	};

	/*!
	 * @brief	Constructor
	 *
	 * @param [in,out]	parent	(Optional) If non-null, the parent.
	 */
	MultiPurposeInputField(QWidget *parent = Q_NULLPTR);
	~MultiPurposeInputField();

	/*!
	 * @brief	Gets maximum size that this component allows user to enter with respect to InputDataType
	 * 			
	 * @returns	The maximum size.
	 */
	unsigned int getMaxSize() const;

	/*!
	 * @brief	Sets maximum size that this component allows
	 *
	 * @param	val	The value.
	 */
	void setMaxSize(unsigned int val);

	/*!
	 * @brief	Obtain the text represented by this input which is only applicable for eINPUT_DATA_TYPE_ASCII
	 *
	 * @returns	The text.
	 */
	std::string getText();

	/*!
	 * @brief	Sets the content
	 * @param	val	The string representation of content
	 */
	void setText(const QString& str);

	/*!
	 * @brief	Obtain the number represented by this input which is only applicable for eINPUT_DATA_TYPE_NUMBER
	 *
	 * @returns	The number.
	 */
	qint64 getNumber();

	/*!
	 * @brief	Obtain the data represented by this input which is only applicable for eINPUT_DATA_TYPE_BINARY_HEX
	 *
	 * @returns	The binary data.
	 */
	QByteArray getBinaryData();

	/*!
	 * @brief	Gets input data type
	 *
	 * @returns	The input data type.
	 */
	MultiPurposeInputField::InputDataType getInputDataType() const;

	/*!
	 * @brief	Sets input data type
	 *          The maximum size that this input component allow. The specific size will be determined with
	            respect to input data type. This is calculated in setInputDataType()
	 * @param	val	The value.
	 */
	void setInputDataType(MultiPurposeInputField::InputDataType val);

private:

	/*! @brief	The user interface configuration file */
	Ui::MultiPurposeInputField ui;

	/*! @brief	The maximum size that this input component allow. The specific size will be determined with
	            respect to input data type. This is calculated in setInputDataType() */
	unsigned int mMaxSize{ 32 };

	/*! @brief	Currently active input mode */
	InputDataType mInputMode{ InputDataType::eINPUT_DATA_TYPE_ASCII };
};
