<div align="center">

# 📦 Product Management System

### *Hệ thống quản lý sản phẩm bằng ngôn ngữ C — Array Version*

![Language](https://img.shields.io/badge/Language-C-blue?logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/Standard-C89%2FC90-orange)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?logo=windows&logoColor=white)
![Storage](https://img.shields.io/badge/Storage-Binary%20File-lightgrey)
![Build](https://img.shields.io/badge/Build-Makefile-success)
![Status](https://img.shields.io/badge/Status-In%20Development-yellow)

</div>

---

## 📖 Giới thiệu

**Product Management System** là chương trình quản lý sản phẩm chạy trên console, được xây dựng bằng ngôn ngữ **C chuẩn C89/C90**. Dữ liệu được lưu trong **mảng tĩnh (Array)** khi chạy và được lưu trữ bền vững xuống **file nhị phân**, hỗ trợ xuất dữ liệu sang nhiều định dạng khác nhau.

Đây là đồ án môn **PRF192 – Programming Fundamentals** tại **FPT University**, được xây dựng theo hướng module hoá: mỗi chức năng được tách riêng thành 1 file `.c`/`.h`, dễ đọc, dễ mở rộng và dễ bảo trì.

---

## ✨ Tổng quan tính năng

| Nhóm | Tính năng |
|---|---|
| 📝 **Quản lý sản phẩm** | Nhập mới (ghi đè), thêm mới (append), xem danh sách (có phân trang), sửa theo ID, chèn vào vị trí bất kỳ, xoá theo ID hoặc xoá toàn bộ |
| 🔍 **Tìm kiếm** | Tìm theo ID, theo tên (không phân biệt hoa/thường), theo giá và theo số lượng (hỗ trợ điều kiện so sánh `>`, `<`, `>=`, `<=`, `=`) |
| ↕️ **Sắp xếp** | Sắp xếp theo ID / Tên / Giá / Số lượng, tăng dần hoặc giảm dần |
| 📊 **Thống kê** | Tổng số sản phẩm, tổng số lượng tồn kho, giá cao nhất, giá thấp nhất, giá trung bình, tổng giá trị kho hàng |
| 📤 **Xuất dữ liệu** | Xuất ra `.txt`, `.csv` (Excel), `.sql` (SQLite) |
| 🧾 **Nhật ký (Log)** | Tự động ghi log mọi thao tác quan trọng (thêm/sửa/xoá/sắp xếp/xuất file), xem lại lịch sử log |
| 🎨 **Giao diện Terminal** | Terminal có màu sắc (Windows API `windows.h`) giúp phân biệt trạng thái thành công / lỗi / cảnh báo trực quan hơn |
| 💾 **Lưu trữ dữ liệu** | Đọc/ghi trực tiếp bằng file nhị phân (`fread`/`fwrite`), đảm bảo dữ liệu không mất khi tắt chương trình |

---

## 🗂 Cấu trúc dự án

```
Array/
├── Makefile                        # Cấu hình build toàn bộ project bằng lệnh `make`
│
├── data/                            # Nơi lưu dữ liệu thực tế của chương trình
│   ├── data.bin                     # File nhị phân lưu danh sách sản phẩm (dữ liệu chính)
│   ├── products.csv                 # Dữ liệu sau khi xuất ra CSV
│   ├── products.sql                 # Dữ liệu sau khi xuất ra SQL
│   └── logger.txt                   # Log lịch sử các thao tác
│
├── docs/
│   └── README.md                    # Tài liệu mô tả dự án
│
├── include/                         # Header (.h) - khai báo hàm, struct, hằng số
│   ├── color.h                      # Khai báo mã màu & hàm đổi màu chữ terminal
│   ├── export.h                     # Khai báo hàm xuất file TXT/CSV/SQL
│   ├── file_io.h                    # Khai báo hàm đọc/ghi file nhị phân
│   ├── logger.h                     # Khai báo hàm ghi & xem log
│   ├── menu.h                       # Khai báo hàm hiển thị menu
│   ├── product.h                    # Định nghĩa struct Product & hằng số chung
│   ├── product_manager.h            # Khai báo các hàm CRUD sản phẩm
│   ├── search.h                     # Khai báo hàm tìm kiếm
│   ├── sort.h                       # Khai báo hàm sắp xếp
│   ├── statistics.h                 # Khai báo hàm thống kê
│   ├── table.h                      # Khai báo hàm in bảng dữ liệu
│   └── validation.h                 # Khai báo hàm nhập & kiểm tra dữ liệu
│
└── src/                              # Source code (.c) - cài đặt logic thực tế
    ├── color.c                      # Cài đặt đổi màu chữ terminal (dùng windows.h)
    ├── export.c                     # Xuất dữ liệu ra TXT / CSV / SQL
    ├── file_io.c                    # Đọc/ghi mảng sản phẩm xuống file .bin
    ├── logger.c                     # Ghi log thao tác & hiển thị lại log
    ├── main.c                       # Điểm khởi đầu, vòng lặp menu chính
    ├── menu.c                       # Hiển thị menu chính & xoá màn hình
    ├── product_manager.c            # Nghiệp vụ CRUD: thêm / sửa / xoá / chèn sản phẩm
    ├── search.c                     # Tìm kiếm sản phẩm theo nhiều điều kiện
    ├── sort.c                       # Sắp xếp sản phẩm (selection sort)
    ├── statistics.c                 # Thống kê số liệu về sản phẩm
    ├── table.c                      # Vẽ bảng dữ liệu ra console (căn cột tự động)
    └── validation.c                 # Nhập & kiểm tra dữ liệu đầu vào an toàn
```

---

## ⚙️ Yêu cầu hệ thống

- Hệ điều hành: **Windows** (do sử dụng `windows.h` cho tính năng đổi màu terminal)
- Compiler hỗ trợ chuẩn **C89/C90**: GCC (MinGW) hoặc tương đương
- Công cụ `make` để build qua `Makefile`

## 🚀 Cài đặt & Chạy chương trình

```bash
# 1. Clone project về máy
git clone https://github.com/<username>/<repo-name>.git
cd Array

# 2. Build chương trình bằng Makefile
make

# 3. Chạy chương trình
management_product_console.exe
```

> 💡 Dữ liệu sẽ tự động được lưu vào thư mục `data/` sau mỗi lần thêm/sửa/xoá, không cần thao tác lưu tay.

---

## 👤 Tác giả

**Chung** — Sinh viên FPT University, chuyên ngành Kỹ thuật phần mềm.

## 📄 License

Dự án phục vụ mục đích học tập — môn **PRF192, FPT University**.