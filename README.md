# Big Integer
ĐỒ ÁN SỐ NGUYÊN LỚN
KIẾN TRÚC MÁY TÍNH VÀ HỢP NGỮ

Ý TƯỞNG THỰC HIỆN 
VÀ MÔI TRƯỜNG LẬP TRÌNH

1.	Ý tưởng thực hiện

a.	Xây dựng dữ liệu
-	Biểu diễn số nguyên lớn qua class QInt có thuộc tính int arrayBits[4] là một mảng kiểu int 4 phần tử, mỗi phần tử là 1 số nguyên kiểu int 4 bytes, mỗi bytes gồm 8 bits tức QInt sẽ có độ dài 128 bits.
-	Mỗi bit sẽ mang giá trị 0 hoặc 1. Bit đầu tiên để xác định số âm hay dương.
-	Dùng hàm getBit() là setBit() để lấy và thay đổi giá trị của các bit.

b.	Phạm vi biểu diễn: từ -2127 đến 2127 - 1.

c.	Chuyển đổi cơ số
-	Hệ thập phân sang hệ nhị phân: Xây dựng hàm chia chuỗi cho 2 rồi lấy số dư đưa vào arrayBits. Nếu là số âm thì chuyển về dạng bù 2.
-	Hệ nhị phân sang hệ thập phân: Nếu là số dương thì cộng dồn các tích của bit 1 với lũy thừa 2 với vị trí tương ứng. Nếu là số âm thì chuyển về dạng dấu lượng, thực hiện như số dương sau đó trả lại dấu ‘-’.
-	Hệ thập lục phân sang nhị phân: Thực hiện chuyển mỗi kí tự trong các kí tự thập lục phân sang 4 kí số nhị phân.
-	Hệ nhị phân sang thập lục phân: Cứ 4 kí số hệ nhị phân nhóm lại tạo thành 1 kí số hệ thập lục phân.
-	Hệ thập phân sang thập lục phân: Chuyển trung gian qua hệ nhị phân.
-	Hệ thập lục phân sang thập phân: Chuyển trung gian qua hệ nhị phân.

d.	Các phép toán đại số
-	Phép cộng: Thực hiện một các tự nhiên bằng cách cộng từng đôi một kí số với nhau và nhớ nếu kết quả vượt 1.
-	Phép trừ: Thực hiện cộng với số bù 2.
-	Phép nhân: Sử dụng thuật toán nhân cải tiến Booth
-	Phép chia: Sử dụng thuật toán nhân 2 số nhị phân.

e.	Các phép toán luận lý
-	Phép AND: Thực hiện & từng cặp phần tử int của hai toán hạng.
-	Phép OR: Thực hiện | từng cặp phần tử int của hai toán hạng.
-	Phép XOR: Thực hiện ^ từng cặp phần tử int của hai toán hạng.
-	Phép NOT: Thực hiện ~ từng cặp phần tử int của hai toán hạng.
 
f.	Các phép dịch và xoay
-	Phép dịch trái: Chuyển thành dạng chuỗi, sau đó thêm kí tự ‘0’ vào cuối và xóa kí tự đầu. Sau đó chuyển lại kiểu QInt.
-	Phép dịch phải: Chuyển thành dạng chuỗi, sau đó xóa kí tự cuối và thêm vào đầu kí tự dấu trước đó. Sau đó chuyển lại kiểu QInt.
-	Phép xoay trái: Chuyển thành dạng chuỗi, sau đó xóa kí tự đầu và thêm kí tự thêm vào cuối kí tự đầu tiên trước khi xóa. Sau đó chuyển lại kiểu QInt.
-	Phép xoay phải: Chuyển thành dạng chuỗi, sau đó xóa kí tự cuối và thêm vào đầu kí tự cuối trước khi xóa. Sau đó chuyển lại kiểu QInt.

2.	Môi trường lập trình

a.	Ngôn ngữ lập trình: C++
b.	IDE: Microsoft Visual Studio 2017
