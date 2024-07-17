#include "MMTStringUtils.h"
#include "MMTFormatUtils.h"

#include <cmath>
#include <iomanip>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <algorithm>

std::uint32_t MMTFormat_STDByteVectorToUINT32_T(std::vector<std::byte> STDByteVector) {
    uint32_t value;
    std::memcpy(&value, STDByteVector.data(), sizeof(uint32_t));
    return value;
}


std::uint32_t MMTFormat_CharArrayToUINT32_T(char* data) {
    return (static_cast<unsigned char>(data[3]) << 24) |
        (static_cast<unsigned char>(data[2]) << 16) |
        (static_cast<unsigned char>(data[1]) << 8) |
        static_cast<unsigned char>(data[0]);
}

std::uint16_t MMTFormat_CharArrayToUINT16_T(char* data) {
    return (static_cast<unsigned char>(data[1]) << 8) |
        static_cast<unsigned char>(data[0]);

}

//ģ��python���[i:i+1] ���ǲ�����i+1��Ч�������������
std::vector<std::byte> MMTFormat_GetRange_Byte(const std::vector<std::byte>& vec, std::size_t startIndex, std::size_t endIndex)
{
    // ��ʼ����������Χ����ڽ������������ؿ�����
    if (startIndex >= vec.size() || startIndex > endIndex)
    {
        return {};
    }

    // ����һ���µ��������洢��Χ�ڵ�Ԫ��
    std::vector<std::byte> rangeVec(endIndex - startIndex);
    // ���Ʒ�Χ�ڵ�Ԫ�ص���������
    std::copy(vec.begin() + startIndex, vec.begin() + endIndex, rangeVec.begin());

    return rangeVec;
}

std::vector<uint32_t> MMTFormat_GetRange_UINT32T(const std::vector<std::uint32_t>& vec, std::size_t startIndex, std::size_t endIndex)
{
    // ��ʼ����������Χ����ڽ������������ؿ�����
    if (startIndex >= vec.size() || startIndex > endIndex)
    {
        return {};
    }

    // ����һ���µ��������洢��Χ�ڵ�Ԫ��
    std::vector<std::uint32_t> rangeVec(endIndex - startIndex);
    // ���Ʒ�Χ�ڵ�Ԫ�ص���������
    std::copy(vec.begin() + startIndex, vec.begin() + endIndex, rangeVec.begin());

    return rangeVec;
}



//��-1.0f���Ե�ǰֵ�ٷ��أ��͵õ���Flip���ֵ
std::vector<std::byte> MMTFormat_Reverse32BitFloatValue(std::vector<std::byte> floatValue) {
    //����Y�ᷭת
    std::vector<std::byte> floatValueReversed = floatValue;

    // ��ȡfloatֵ
    float y_value;
    std::memcpy(&y_value, floatValueReversed.data(), sizeof(float));

    // ��תYֵ
    y_value *= -1.0f;

    // ����ת���ֵд��vector
    std::memcpy(floatValueReversed.data(), &y_value, sizeof(float));
    return floatValueReversed;
}


std::vector<std::byte> MMTFormat_Reverse16BitShortValue(std::vector<std::byte> shortValue) {
    // ���з�ת
    std::vector<std::byte> shortValueReversed = shortValue;

    // ��ȡ short ֵ
    short y_value;
    std::memcpy(&y_value, shortValueReversed.data(), sizeof(short));

    // ��ת Y ֵ
    y_value *= -1;

    // ����ת���ֵд�� vector
    std::memcpy(shortValueReversed.data(), &y_value, sizeof(short));
    return shortValueReversed;
}





std::wstring MMTFormat_NearestFormatedFloat(std::wstring originalValue, int reserveCount) {
    //LOG.LogOutput(L"Calculate nearestFormatedFloat");
    std::vector<std::wstring> split_results;
    boost::split(split_results, originalValue, boost::is_any_of(","));
    //LOG.LogOutput(L"Split originalValue over, size: " + std::to_wstring(split_results.size()));
    std::vector<std::wstring> str_results;

    for (std::wstring value : split_results) {
        boost::algorithm::trim(value);
        std::wstring valueDoubleStr;
        if (value == L"-nan(ind)") {
            valueDoubleStr = L"0";
        }
        else {
            //���������������ý���ֵ
            double valueDouble = boost::lexical_cast<double>(value);
            if (std::fabs(valueDouble) < 0.0001) {
                valueDouble = 0.0;
            }

            std::ostringstream out_stream_value;
            out_stream_value << std::fixed << std::setprecision(reserveCount) << valueDouble;
            valueDoubleStr = MMTString_ToWideString(out_stream_value.str());

            if (valueDouble == 0.0) {
                valueDoubleStr = L"0";
            }
        }


        str_results.push_back(valueDoubleStr);
    }
    std::wstring finalStr = L"";
    for (size_t i = 0; i < str_results.size(); i++)
    {
        std::wstring str = str_results[i];
        if (i != str_results.size() - 1) {
            finalStr = finalStr + str + L"_";
        }
        else {
            finalStr = finalStr + str;
        }
    }

    return finalStr;
}


// ���������ĳ���
double VectorLength(const Vector3D& vector) {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}


// ���������ĵ�λ����������һ��������
Vector3D NormalizeVector(const Vector3D vector) {
    double length = VectorLength(vector);
    Vector3D normalizedVector;
    normalizedVector.x = vector.x / length;
    normalizedVector.y = vector.y / length;
    normalizedVector.z = vector.z / length;
    return normalizedVector;
}


//���
Vector3D AddVectors(const Vector3D vector1, const Vector3D vector2) {
    Vector3D result;
    result.x = vector1.x + vector2.x;
    result.y = vector1.y + vector2.y;
    result.z = vector1.z + vector2.z;
    return result;
}



std::wstring MMTFormat_FormatedFloat(double originalValue, int reserveCount) {
    std::wstring valueDoubleStr;

    double valueDouble = originalValue;
    if (std::fabs(valueDouble) < 0.0001) {
        valueDouble = 0.0;
    }

    std::ostringstream out_stream_value;
    out_stream_value << std::fixed << std::setprecision(reserveCount) << valueDouble;
    valueDoubleStr = MMTString_ToWideString(out_stream_value.str());

    if (valueDouble == 0.0) {
        valueDoubleStr = L"0";
    }
    return valueDoubleStr;
}


//ֻ��0��255
std::byte MMTFormat_PackNumberToByte(std::uint32_t number)
{
    std::byte packedByte = std::byte(number & 0xFF);
    return packedByte;
}


//�Ľ���ķ���
std::vector<std::byte> MMTFormat_PackNumberR32_FLOAT_littleIndian(float number)
{
    std::vector<std::byte> packedBytes(sizeof(float));

    std::memcpy(packedBytes.data(), &number, sizeof(float));

    return packedBytes;
}


std::vector<std::vector<double>> MMTFormat_NormalNormalizeStoreTangent(const std::vector<std::vector<double>> positions, const std::vector<std::vector<double>> normals) {

    // keyΪposition��valueΪnormal
    std::unordered_map<std::wstring, std::wstring> position_normalSum_map;
    std::unordered_map<std::wstring, int> position_normalNumber_map;

    // ���
    for (int i = 0; i < positions.size(); i++) {
        std::vector<double> position_double = positions[i];
        std::vector<double> normal_double = normals[i];

        //�ֱ�ת��Ϊwstring
        std::wstring formated_position = MMTFormat_FormatedFloat(position_double[0], 10) + L"_" + MMTFormat_FormatedFloat(position_double[1], 10) + L"_" + MMTFormat_FormatedFloat(position_double[2], 10);
        std::wstring formated_normal = MMTFormat_FormatedFloat(normal_double[0], 10) + L"_" + MMTFormat_FormatedFloat(normal_double[1], 10) + L"_" + MMTFormat_FormatedFloat(normal_double[2], 10);

        if (position_normalSum_map.contains(formated_position)) {
            std::wstring old_formated_normal = position_normalSum_map[formated_position];
            std::vector<std::wstring> split_results;
            boost::split(split_results, old_formated_normal, boost::is_any_of("_"));

            double sum_x = (std::stod(split_results[0]) + normal_double[0]);
            double sum_y = (std::stod(split_results[1]) + normal_double[1]);
            double sum_z = (std::stod(split_results[2]) + normal_double[2]);
            //Ȼ����ת����wstring���Ż�
            std::wstring result_formated_normal = MMTFormat_FormatedFloat(sum_x, 10) + L"_" + MMTFormat_FormatedFloat(sum_y, 10) + L"_" + MMTFormat_FormatedFloat(sum_z, 10);
            position_normalSum_map[formated_position] = result_formated_normal;
            int number = position_normalNumber_map[formated_position];
            position_normalNumber_map[formated_position] = number + 1;
        }
        else {
            position_normalSum_map[formated_position] = formated_normal;
            position_normalNumber_map[formated_position] = 1;
        }

    }

    std::unordered_map<std::wstring, std::wstring> position_normal_final_map;

    //�ó�ÿһ������Ȼ����������Ȼ���[-1,1]��һ����[0,1] ,�ŵ����յ�����
    for (const auto& pair : position_normalSum_map) {
        std::wstring position = pair.first;
        std::wstring normal_val = pair.second;

        std::vector<std::wstring> split_results;
        boost::split(split_results, normal_val, boost::is_any_of("_"));

        double avg_val_x = std::stod(split_results[0]) / position_normalNumber_map[position];
        double avg_val_y = std::stod(split_results[1]) / position_normalNumber_map[position];
        double avg_val_z = std::stod(split_results[2]) / position_normalNumber_map[position];

        double normalize_val_x = (avg_val_x + 1) / 2;
        double normalize_val_y = (avg_val_y + 1) / 2;
        double normalize_val_z = (avg_val_z + 1) / 2;


        std::wstring result_formated_normal = MMTFormat_FormatedFloat(normalize_val_x, 10) + L"_" + MMTFormat_FormatedFloat(normalize_val_y, 10) + L"_" + MMTFormat_FormatedFloat(normalize_val_z, 10);
        position_normal_final_map[position] = result_formated_normal;
    }

    //���ﷵ�ص���ÿ��position��Ӧ��tangent
    std::vector<std::vector<double>> tangents;
    //�������ٴα���
    for (int i = 0; i < positions.size(); i++) {
        std::vector<double> position_double = positions[i];
        //�ֱ�ת��Ϊwstring
        std::wstring formated_position = MMTFormat_FormatedFloat(position_double[0], 10) + L"_" + MMTFormat_FormatedFloat(position_double[1], 10) + L"_" + MMTFormat_FormatedFloat(position_double[2], 10);
        //Ȼ������Ǹ�map��ȡ��Ӧ��tangent��Ϣ
        std::wstring formated_normal = position_normal_final_map[formated_position];
        std::vector<std::wstring> split_results;
        boost::split(split_results, formated_normal, boost::is_any_of("_"));
        std::vector<double> OldNormalVector = { std::stod(split_results[0]),std::stod(split_results[1]) ,std::stod(split_results[2]) ,0 };
        tangents.push_back(OldNormalVector);
    }

    return tangents;
}




// ����ƽ�����ߣ�����ֻ�Ǽ���ƽ�����ߣ���ʵҲ����Normalֵ������Ҫ����Normalֵ������TANGENT���С�
std::vector<std::vector<double>> MMTFormat_CalculateAverageNormalsAndStoreTangent(const std::vector<std::vector<double>> positions, const std::vector<std::vector<double>> normals) {


    // keyΪposition��valueΪnormal
    std::unordered_map<std::wstring, std::wstring> position_normal_map;

    //�߼����£�
    //����Ѵ��ڴ�position��string�����ó�wstring�������������뵱ǰnormal��ӣ������һ������ת��Ϊwstring�Ż�ȥ
    // ��������ڣ���ֱ�����

    for (int i = 0; i < positions.size(); i++) {
        std::vector<double> position_double = positions[i];
        std::vector<double> normal_double = normals[i];

        //�ֱ�ת��Ϊwstring
        std::wstring formated_position = MMTFormat_FormatedFloat(position_double[0], 10) + L"_" + MMTFormat_FormatedFloat(position_double[1], 10) + L"_" + MMTFormat_FormatedFloat(position_double[2], 10);
        std::wstring formated_normal = MMTFormat_FormatedFloat(normal_double[0], 10) + L"_" + MMTFormat_FormatedFloat(normal_double[1], 10) + L"_" + MMTFormat_FormatedFloat(normal_double[2], 10);

        if (position_normal_map.contains(formated_position)) {
            std::wstring old_formated_normal = position_normal_map[formated_position];
            std::vector<std::wstring> split_results;
            boost::split(split_results, old_formated_normal, boost::is_any_of("_"));

            Vector3D OldNormalVector = { std::stod(split_results[0]),std::stod(split_results[1]) ,std::stod(split_results[2]) };
            Vector3D NowNormalVector = { normal_double[0], normal_double[1], normal_double[2] };
            Vector3D newVector = NormalizeVector(AddVectors(OldNormalVector, NowNormalVector));
            //Ȼ����ת����wstring���Ż�
            std::wstring result_formated_normal = MMTFormat_FormatedFloat(newVector.x, 10) + L"_" + MMTFormat_FormatedFloat(newVector.y, 10) + L"_" + MMTFormat_FormatedFloat(newVector.z, 10);
            position_normal_map[formated_position] = result_formated_normal;
        }
        else {
            Vector3D NowNormalVector = { normal_double[0], normal_double[1], normal_double[2] };
            Vector3D newVector = NormalizeVector(NowNormalVector);
            //Ȼ����ת����wstring���Ż�
            std::wstring result_formated_normal = MMTFormat_FormatedFloat(newVector.x, 10) + L"_" + MMTFormat_FormatedFloat(newVector.y, 10) + L"_" + MMTFormat_FormatedFloat(newVector.z, 10);
            position_normal_map[formated_position] = result_formated_normal;
        }

    }
    //LOG.LogOutput(L"Size of position_normal_map: " + std::to_wstring(position_normal_map.size()));

    //���ﷵ�ص���ÿ��position��Ӧ��tangent
    std::vector<std::vector<double>> tangents;
    //�������ٴα���
    for (int i = 0; i < positions.size(); i++) {
        std::vector<double> position_double = positions[i];
        //�ֱ�ת��Ϊwstring
        std::wstring formated_position = MMTFormat_FormatedFloat(position_double[0], 10) + L"_" + MMTFormat_FormatedFloat(position_double[1], 10) + L"_" + MMTFormat_FormatedFloat(position_double[2], 10);
        //Ȼ������Ǹ�map��ȡ��Ӧ��tangent��Ϣ
        std::wstring formated_normal = position_normal_map[formated_position];
        std::vector<std::wstring> split_results;
        boost::split(split_results, formated_normal, boost::is_any_of("_"));
        std::vector<double> OldNormalVector = { std::stod(split_results[0]),std::stod(split_results[1]) ,std::stod(split_results[2]) ,0 };
        tangents.push_back(OldNormalVector);
    }

    return tangents;
}




double MMTFormat_ByteVectorToFloat(const std::vector<std::byte>& bytes) {
    // ����ֽ�����ĳ���
    if (bytes.size() != sizeof(float)) {
        //throw std::runtime_error("�ֽ�����ĳ�����float���͵Ĵ�С��ƥ��");
    }

    // ���ֽ���������ݸ��Ƶ�32λ�������ͣ�����С����
    std::uint32_t value = 0;
    for (std::size_t i = 0; i < sizeof(float); ++i) {
        value |= static_cast<std::uint32_t>(static_cast<std::uint8_t>(bytes[i])) << (8 * i);
    }

    // ����������Ϊfloat���͵�ֵ
    float result;
    std::memcpy(&result, &value, sizeof(float));
    return result;
}



std::wstring MMTFormat_NearestFloat(std::wstring originalValue) {
    std::vector<std::wstring> split_results;
    boost::split(split_results, originalValue, boost::is_any_of(","));

    std::vector<std::wstring> str_results;
    for (std::wstring value : split_results) {
        boost::algorithm::trim(value);
        std::wstring valueDoubleStr;
        if (value == L"-nan(ind)") {
            valueDoubleStr = L"0";
        }
        else {
            // //���������������ý���ֵ
            //double valueDouble = boost::lexical_cast<double>(value);
            //if (std::fabs(valueDouble) < 0.0001) {
            //    valueDouble = 0.0;
            //}

            //std::ostringstream out_stream_value;
            //out_stream_value << std::fixed << std::setprecision(10) << valueDouble;
            //valueDoubleStr = out_stream_value.str();

            //if (valueDouble == 0.0) {
            //    valueDoubleStr = "0";
            //}
            valueDoubleStr = value;
        }


        str_results.push_back(valueDoubleStr);
    }

    std::wstring finalStr = L"";
    for (size_t i = 0; i < str_results.size(); i++)
    {
        std::wstring str = str_results[i];
        if (i != str_results.size() - 1) {
            finalStr = finalStr + str + L", ";
        }
        else {
            finalStr = finalStr + str;
        }
    }

    return finalStr;
}


// ��Ϊ����UE4��NORMALֵ��SNORM���ͣ����Բ���Ҫ4�����ȣ�ֻҪ1�����ȣ�Ҳ���ǲ�һ�������ˡ�
std::vector<std::byte> MMTFormat_PackNumberOneByte(int packNumber)
{
    std::vector<std::byte> packedByte(1);
    packedByte[0] = std::byte(packNumber);  // 0x7F Ϊֱ�Ӵ洢��ֵ127��������Ϊ���������int8����ô1.0f * 127�͵õ���0x7F��Ҳ���Ǳ�ʾ1.0f
    // ���ﲻ��0x3F����0x7F��˵��Normal��Tangent������ԭ����Normal��Tangent����Float����ǿ��ת��Ϊint8���ͼ� -126-127 ֮���ֵ�õ��ġ�
    // ת���㷨Ϊ float * 127
    // NORMAL ֵӦ������ĳ��ƽ�������㷨�������������ͬ�Ķ��㹲����ͬ���ߣ�
    // TANGENT Ӧ������AverageNormal�ٹ�һ���㷨
    return packedByte;
}

////��-1.0f���Ե�ǰֵ�ٷ��أ��͵õ���Flip���ֵ
std::vector<std::byte> MMTFormat_ReverseSNORMValue(std::vector<std::byte>& snormValue) {
    // ȷ���������ڴ����ֽ�����
    if (snormValue.size() != 1) {
        return snormValue;
    }

    // ��ȡsnormֵ��ע�� static_cast ��Ϊ��ת�� std::byte ������
    int8_t value = static_cast<int8_t>(snormValue[0]);

    // ��תsnormֵ
    // ֱ��ʹ�������������� std::numeric_limits
    if (value == -128) {
        // ���������-128���෴������SNORM��ʾ��Χ�ڵ�ֵ����������ʹ��127
        value = 127;
    }
    else {
        // ȡ�෴��
        value = -value;
    }

    // �洢��ת���ֵ
    snormValue[0] = static_cast<std::byte>(value);

    return snormValue;
}


std::byte MMTFormat_ReverseSNORMValueSingle(std::byte Value) {
    
    // ��ȡsnormֵ��ע�� static_cast ��Ϊ��ת�� std::byte ������
    int8_t value = static_cast<int8_t>(Value);

    // ��תsnormֵ
    // ֱ��ʹ�������������� std::numeric_limits
    if (value == -128) {
        // ���������-128���෴������SNORM��ʾ��Χ�ڵ�ֵ����������ʹ��127
        value = 127;
    }
    else {
        // ȡ�෴��
        value = -value;
    }

    return static_cast<std::byte>(value);
}


std::byte MMTFormat_UnormToSNORMValueSingle(std::byte Value) {
    // UNORM range: [0, 255]
    // SNORM range: [-127, 127]

    // Normalize the UNORM value to the range [0.0, 1.0]
    float fValue = static_cast<float>(static_cast<unsigned int>(Value)) / 255.0f;

    // Convert the normalized value to the SNORM range [-1.0, 1.0]
    float fSNORMValue = fValue * 2.0f - 1.0f;

    // Clamp the SNORM value to the valid range [-1.0, 1.0]
    if (fSNORMValue < -1.0f) {
        fSNORMValue = -1.0f;
    }
    else if (fSNORMValue > 1.0f) {
        fSNORMValue = 1.0f;
    }

    // Convert the SNORM value to a std::byte
    return static_cast<std::byte>(static_cast<int>(fSNORMValue * 127.0f));
}


std::vector<std::byte> MMTFormat_IntToByteVector(int value) {
    std::vector<std::byte> bytes(4);
    bytes[3] = static_cast<std::byte>((value >> 24) & 0xFF);
    bytes[2] = static_cast<std::byte>((value >> 16) & 0xFF);
    bytes[1] = static_cast<std::byte>((value >> 8) & 0xFF);
    bytes[0] = static_cast<std::byte>(value & 0xFF);
    return bytes;
}