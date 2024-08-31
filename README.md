# Smart Home
Dự án "Smart Home" là một hệ thống cổng ra vào thông minh tích hợp xử lý ảnh để điều khiển, được phát triển bởi nhóm 3 thành viên. Dự án sử dụng vi điều khiển ESP32 để quản lý các thiết bị trong ngôi nhà thông minh như đèn, quạt và cửa tự động.

## Mô tả Dự Án
- Hệ thống cổng ra vào thông minh: Tích hợp công nghệ xử lý ảnh để nhận diện và điều khiển cổng ra vào (chưa hoàn thiện).
- Quản lý thiết bị: Sử dụng ESP32 để điều khiển cửa tự động.
- Xử lý yêu cầu điều khiển: Thiết kế và triển khai quy trình xử lý yêu cầu điều khiển cho ESP32 sử dụng ESP-IDF.
- Kênh giao tiếp MQTT: Thiết lập kênh giao tiếp hai chiều giữa ESP32 và các hệ thống backend thông qua MQTT.
## Cài Đặt
Clone repository:

```bash Copy code

git clone https://github.com/TungHu/Do_An_1.git
```

Cài đặt ESP-IDF: Làm theo hướng dẫn tại trang chính của ESP-IDF.

Cài đặt thư viện cần thiết:


Biên dịch và tải chương trình lên ESP32:

Điều khiển thiết bị: Các thiết bị có thể được điều khiển qua hệ thống cổng ra vào thông minh và các yêu cầu sẽ được gửi qua giao tiếp MQTT.
Xử lý ảnh: Hệ thống xử lý ảnh tích hợp sẽ nhận diện các đối tượng và điều khiển cổng ra vào dựa trên kết quả xử lý.
Liên Hệ
Nếu bạn có bất kỳ câu hỏi nào hoặc cần hỗ trợ, vui lòng liên hệ qua [email của bạn] hoặc tạo một issue trên trang GitHub này.

## Tài Liệu Tham Khảo
- ESP-IDF Documentation
- MQTT Protocol
