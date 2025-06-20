#include "scisdk_core.h"

#include <chrono>
#include <thread>
#include <iostream>

SciSDK::SciSDK() {

}
SciSDK::~SciSDK() {

}

NI_RESULT SciSDK::AddNewDevice(string DevicePath, string DeviceModel, string JSONFwFilePath, string Name) {

	std::cout << "Finding device by name.\n";
	if (FindDeviceByName(Name) != NULL){
		std::cout << "Device already exists!\n";
		return NI_DEVICE_NAME_ALREADY_EXISTS;
	}
	std::cout << "Device name did not exist. Creating...\n";
	SciSDK_Device * newDev;
	newDev = new SciSDK_Device(DevicePath, DeviceModel, JSONFwFilePath, Name);
	std::cout << "SciSDK_Device constructed.\n";
	NI_RESULT err_cnt = newDev->Connect();
	if (err_cnt != NI_OK) {
		std::cout << "err_cnt: " << err_cnt << std::endl;
		return err_cnt;
	}
	else {
		devs.push_back(newDev);
		std::cout << "NI_OK\n";
		return NI_OK;
	}
}

NI_RESULT SciSDK::DetachDevice(string Name) {
	int res = NI_ERROR;
	SciSDK_Device* device = FindDeviceByName(Name);
	if (device != NULL) {
		res = device->CloseConnection();
	}
	devs.remove(device);
	return res;
}

NI_RESULT SciSDK::SetRegister(string Path, uint32_t value) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->SetRegister(subpath, value);

}

NI_RESULT SciSDK::GetRegister(string Path, uint32_t *value) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->GetRegister(subpath, value);

	return NI_OK;
}

NI_RESULT SciSDK::StrobeRegister(string Path, string strobe_polarity) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;

	if ((strobe_polarity == "positive") || (strobe_polarity == "pos")) {
		ret |= dev->SetRegister(subpath, 0);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		ret = dev->SetRegister(subpath, 1);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		ret |= dev->SetRegister(subpath, 0);
	}
	else
	{
		ret |= dev->SetRegister(subpath, 1);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		ret = dev->SetRegister(subpath, 0);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		ret |= dev->SetRegister(subpath, 1);
	}
	return ret;
}

NI_RESULT SciSDK::SetParameter(string Path, uint32_t value) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->SetParameter(subpath, value);
}

NI_RESULT SciSDK::GetParameter(string Path, uint32_t *value) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->GetParameter(subpath, value);
}

NI_RESULT SciSDK::SetParameter(string Path, int32_t value) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->SetParameter(subpath, value);
}

NI_RESULT SciSDK::GetParameter(string Path, int32_t *value) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->GetParameter(subpath, value);
}

NI_RESULT SciSDK::SetParameter(string Path, uint64_t value) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->SetParameter(subpath, value);
}

NI_RESULT SciSDK::GetParameter(string Path, uint64_t *value) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->GetParameter(subpath, value);
}

NI_RESULT SciSDK::SetParameter(string Path, int64_t value) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->SetParameter(subpath, value);
}

NI_RESULT SciSDK::GetParameter(string Path, int64_t *value) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->GetParameter(subpath, value);
}

NI_RESULT SciSDK::SetParameter(string Path, double value) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->SetParameter(subpath, value);
}

NI_RESULT SciSDK::GetParameter(string Path, double *value) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->GetParameter(subpath, value);
}

NI_RESULT SciSDK::SetParameter(string Path, string value) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->SetParameter(subpath, value);
}

NI_RESULT SciSDK::GetParameter(string Path, string *value) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->GetParameter(subpath, value);
}


NI_RESULT SciSDK::ExecuteCommand(string Path, string parameter) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->ExecuteCommand(subpath);
}

NI_RESULT SciSDK::AllocateBuffer(string Path, T_BUFFER_TYPE bt, void **buffer) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->AllocateBuffer(subpath, bt, buffer);
}

NI_RESULT SciSDK::AllocateBuffer(string Path, T_BUFFER_TYPE bt, void **buffer, int size) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->AllocateBuffer(subpath, bt, buffer, size);
}
NI_RESULT SciSDK::FreeBuffer(string Path, T_BUFFER_TYPE bt, void **buffer) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->FreeBuffer(subpath, bt, buffer);
}

NI_RESULT SciSDK::ReadData(string Path, void *buffer) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->ReadData(subpath, buffer);
}

NI_RESULT SciSDK::ReadStatus(string Path, void *buffer) {
	SciSDK_Device * dev;
	string subpath;
	int ret;
	if ((ret = LocateDevice(Path, &dev, &subpath)) != 0) return ret;
	return dev->ReadStatus(subpath, buffer);
}

NI_RESULT SciSDK::DecodeData(string Path, void *buffer_in, void *buffer_out) {

	return NI_OK;
}

NI_RESULT SciSDK::GetComponentList(string name, string Type, string *res, bool return_json)
{
	vector<SciSDK_Device*> dev_vector{ std::begin(devs), std::end(devs) };
	for (int i = 0; i < devs.size(); i++) {
		if (dev_vector.at(i)->GetName() == name) {
			int r =  dev_vector.at(i)->GetComponentList(Type, res, return_json);
			return r;
		}
	}
	return NI_ERROR;
}

NI_RESULT SciSDK::GetAllParameters(string path, string * ret)
{
	string device_name = SplitPath(path, ':').at(0);
	SciSDK_Device* device = FindDeviceByName(device_name);
	if (device != NULL) {
		return device->GetAllParameters(path, ret);
	}
	return NI_ERROR;
}

NI_RESULT SciSDK::GetParameterDescription(string path, string * ret)
{
	string device_name = SplitPath(path, ':').at(0);
	SciSDK_Device* device = FindDeviceByName(device_name);
	if (device != NULL) {
		return device->GetParameterDescription(path, ret);
	}
	return NI_ERROR;
}

NI_RESULT SciSDK::GetParameterListOfValues(string path, string * ret)
{
	string device_name = SplitPath(path, ':').at(0);
	SciSDK_Device* device = FindDeviceByName(device_name);
	if (device != NULL) {
		return device->GetParameterListOfValues(path, ret);
	}
	return NI_ERROR;
}

NI_RESULT SciSDK::GetParameterMinimumValue(string path, double * ret)
{
	string device_name = SplitPath(path, ':').at(0);
	SciSDK_Device* device = FindDeviceByName(device_name);
	if (device != NULL) {
		return device->GetParameterMinimumValue(path, ret);
	}
	return NI_ERROR;
}

NI_RESULT SciSDK::GetParameterMaximumValue(string path, double * ret)
{
	string device_name = SplitPath(path, ':').at(0);
	SciSDK_Device* device = FindDeviceByName(device_name);
	if (device != NULL) {
		return device->GetParameterMaximumValue(path, ret);
	}
	return NI_ERROR;
}

NI_RESULT SciSDK::GetParametersProperties(string path, string* ret)
{
	string device_name = SplitPath(path, ':').at(0);
	SciSDK_Device* device = FindDeviceByName(device_name);
	if (device != NULL) {
		return device->GetParametersProperties(path, ret);
	}
	return NI_ERROR;
}

NI_RESULT SciSDK::GetAttachedDevicesList(string* devices)
{
	int attached_devices_count = devs.size();
	*devices = "";

	for (auto elem : devs) {
		*devices += elem->GetName() + ";";
	}

	return NI_OK;
}

NI_RESULT SciSDK::GetLibraryVersion(string* ret)
{
	*ret = SCISDK_VERSION;
	return NI_OK;
}

SciSDK_Device * SciSDK::FindDeviceByName(string Name) {
	std::list<SciSDK_Device *>::iterator it;
	//std::cout << "begin: " << devs.begin() << ", end: " << devs.end() << std::endl;
	std::cout << "begin iteration! Checking against " << Name << std::endl;
	for (it = devs.begin(); it != devs.end(); ++it) {
		std::cout << "next iteration. End? " << (it == devs.end()) << std::endl;
		//std::cout << "it: " << it << std::endl;
		//std::cout << "name: " << (*it)->GetName() << std::endl;
		if ((*it)->GetName() == Name) {
			std::cout << "Found device by name!\n";
			return *it;
		}
		std::cout << "got a different value; continuing\n";
	}
	std::cout << "nothing found in SciSDK::FindDeviceByName; returning NULL\n";
	return NULL;
}

std::vector<std::string> SciSDK::SplitPath(string path, char separator) {

	std::stringstream test(path);
	std::string segment;
	std::vector<std::string> seglist;

	while (std::getline(test, segment, separator))
	{
		seglist.push_back(segment);
	}
	return seglist;

}

NI_RESULT SciSDK::LocateDevice(string path, SciSDK_Device **dev, string *subpath) {
	vector<string> qPP = SplitPath(path, ':');
	if (qPP.size() != 2) return NI_INVALID_PATH;
	string devname = qPP[0];
	*subpath = qPP[1];
	*dev = FindDeviceByName(devname);
	if (!*dev) return NI_NOT_FOUND;
	return NI_OK;
}

string SciSDK::s_error(int err_no) {

	switch (err_no) {
	case NI_OK:
		return "ok";
	case NI_ERROR_GENERIC:
		return "generic error";
	case NI_ERROR_INTERFACE:
		return "hardware interface error";
	case NI_ERROR_FPGA:
		return "fpga core return an error";
	case NI_ERROR_TRANSFER_MAX_LENGTH:
		return "transfer length exeed maximum limit";
	case NI_ERROR_NOTCONNECTED:
		return "hardware not connected";
	case NI_NO_DATA_AVAILABLE:
		return "no data available";
	case NI_TOO_MANY_DEVICES_CONNECTED:
		return "too many device connected";
	case NI_INVALID_HANDLE:
		return "handle is not valid";
	case NI_INVALID_KEY:
		return "json key not valid, error in json file";
	case NI_INVALID_PARAMETER:
		return "parameter does not exists";
	case NI_PARAMETER_OUT_OF_RANGE:
		return "parameter out of range";
	case NI_INCOMPLETE_READ:
		return "read not completed";
	case NI_INVALID_COMMAND:
		return "invalid command";
	case NI_ALREADY_CONNECTED:
		return "already connected to hardware";
	case NI_ALLOC_FAILED:
		return "alloc failed, out of memory";
	case NI_MEMORY_NOT_ALLOCATED:
		return "memory is not allocated, nullptr";
	case NI_INVALID_BUFFER_TYPE:
		return "invalid buffer type";
	case NI_INVALID_BUFFER_SIZE:
		return "invalid buffer size";
	case NI_INCOMPATIBLE_BUFFER:
		return "incompatible buffer specs";
	case NI_INVALID_BUFFER:
		return "invalid buffer";
	case NI_TIMEOUT:
		return "timeout";
	case NI_INVALID_CFG_JSON:
		return "config json is not valid, error in file";
	case NI_CFG_JSON_NOT_FOUND:
		return "config json not found";
	case NI_DEVICE_NAME_ALREADY_EXISTS:
		return "device name already exists";
	case NI_INVALID_PATH:
		return "invalid path";
	case NI_NOT_FOUND:
		return "not found";
	case NI_INVALID_TYPE:
		return "invalid type";
	case NI_ALREADY_RUNNING:
		return "already running";
	case NI_NOT_RUNNING:
		return "not running";
	case NI_NOT_ARMED:
		return "not armed";
	case NI_SPECIFIC_ERROR:
		return "specific error";
	default:
		return "error description not available";
	}

}

void SciSDK::p_error(int err_no) {
	if (err_no != NI_OK) {
		cerr << "0x" << std::hex << err_no;
		cerr << " - " << s_error(err_no) << endl;
	}
}

void SciSDK::p_error(string fnc, int err_no) {
	if (err_no != NI_OK) {
		cerr << fnc << " : ";
		cerr << "0x" << std::hex << err_no;
		cerr << " - " << s_error(err_no) << endl;
	}
}

void SciSDK::p_error(int line, int err_no) {
	if (err_no != NI_OK) {
		cerr << "LINE " << line << " : ";
		cerr << "0x" << std::hex << err_no;
		cerr << " - " << s_error(err_no) << endl;
	}
}

void SciSDK::p_error(string file, int line, int err_no) {
	if (err_no != NI_OK) {
		cerr << file << " : ";
		cerr << "LINE " << line << " : ";
		cerr << "0x" << std::hex << err_no;
		cerr << " - " << s_error(err_no) << endl;
	}
}
