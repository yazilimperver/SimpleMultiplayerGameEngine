#include "MultiPurposeInputField.h"

MultiPurposeInputField::MultiPurposeInputField(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

MultiPurposeInputField::~MultiPurposeInputField()
{
}

unsigned int MultiPurposeInputField::getMaxSize() const
{
	return mMaxSize;
}

void MultiPurposeInputField::setMaxSize(unsigned int val)
{
	mMaxSize = val;
	ui.inputField->setMaxLength(val);
	this->setInputDataType(mInputMode);
}

qint64 MultiPurposeInputField::getNumber()
{
	// TBD: add extra controls
	return ui.inputField->text().toInt();
}

std::string MultiPurposeInputField::getText()
{
	// TBD: add extra controls
	return ui.inputField->text().toStdString();
}

QByteArray MultiPurposeInputField::getBinaryData()
{
	// TBD: add extra controls
	return QByteArray::fromHex(ui.inputField->text().toLatin1());
}

MultiPurposeInputField::InputDataType MultiPurposeInputField::getInputDataType() const
{
	return mInputMode;
}

void MultiPurposeInputField::setInputDataType(InputDataType val)
{
	mInputMode = val;
	ui.inputField->setText("");

	switch (mInputMode)
	{
	case MultiPurposeInputField::InputDataType::eINPUT_DATA_TYPE_ASCII:
		ui.inputField->setMaxLength(mMaxSize);
		ui.inputField->setInputMask("");
		break;
	case MultiPurposeInputField::InputDataType::eINPUT_DATA_TYPE_BINARY_HEX:
		ui.inputField->setMaxLength(mMaxSize * 3);
		ui.inputField->setInputMask(">" + QString("HH:").repeated(mMaxSize));
		break;
	case MultiPurposeInputField::InputDataType::eINPUT_DATA_TYPE_NUMBER:
		ui.inputField->setMaxLength(mMaxSize);
		ui.inputField->setInputMask(QString("9").repeated(mMaxSize));
		break;
	default:
		break;
	}
}
