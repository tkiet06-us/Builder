#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

// "Slide code 1"

// 1. PRODUCT (Sản phẩm đầu ra)
// Là một sản phẩm cụ thể

// A. Ngôi nhà thật 
class House {
private:
    string foundationType;
    string wallType;
    string floorType;

    int rooms;
    int windows;

    string roofType;

    bool hasPool;
    bool hasGarden;
    bool hasGarage;

    // Constructor của Product được set trong private
    // --> Chỉ được tạo đối tượng từ builder
    // --> Thêm hàm bạn Concrete Builder để nó có thể tạo sản phẩm thông qua constructor này
    friend class HouseBuilder;

    House(string foundation, string wall, string floor, int room, int window, string roof, bool pool, bool garden, bool garage) :
        foundationType(foundation), wallType(wall), floorType(floor), rooms(room), windows(window), roofType(roof), hasPool(pool), hasGarden(garden), hasGarage(garage) {
    }

public:
    // Trình bày sản phẩm: Hiển thị ngôi nhà hoàn chỉnh - các phần đã hoàn thành
    void showHouse() {
        cout << "   [Ket qua: Ban da nhan duoc ngoi nha]:" << endl;
        cout << "    - Da hoan thien: Do mong loai " << foundationType << endl;
        cout << "    - Da hoan thien: Tuong loai bang " << wallType << endl;
        cout << "    - Da hoan thien: San nha " << floorType << endl;
        cout << "    - Da hoan thien: Xay " << rooms << " can phong" << endl;
        cout << "    - Da hoan thien: Lap dat " << windows << " cua so" << endl;
        cout << "    - Da hoan thien: Lop mai " << roofType << endl;
        if (hasPool) {
            cout << "    - Da hoan thien: Ho boi" << endl;
        }
        if (hasGarden) {
            cout << "    - Da hoan thien: Phan dat cho khu vuon" << endl;
        }
        if (hasGarage) {
            cout << "    - Da hoan thien: Garage cho xe hoi" << endl;
        }
        cout << "    -> San sang don do dac vao nha o!" << endl;
    }
};

// B.Báo cáo thi công (Construction Report)
class ConstructionReport {
private:
    int tonsOfCement;
    int tonsOfMetal;
    int numBricks;
    int numTiles;
    int m3OfWood;
    int m2OfGlass;

    friend class EstimatorBuilder;

    ConstructionReport(int cement, int metal, int brick, int tile, int wood, int glass) :
        tonsOfCement(cement), tonsOfMetal(metal), numBricks(brick), numTiles(tile), m3OfWood(wood), m2OfGlass(glass) {
    }

public:
    // Trình bày sản phẩm: Hiển thị báo cáo dự toán nguyên vật liệu
    void showReport() {
        cout << "   [Ket qua: Bao cao du toan vat lieu]:" << endl;
        cout << "    - Xi mang da dung: " << tonsOfCement << " tan" << endl;
        cout << "    - Kim loai da dung: " << tonsOfMetal << " tan" << endl;
        cout << "    - Gach da xay: " << numBricks << " vien" << endl;
        cout << "    - Gach san da lat: " << numTiles << " vien" << endl;
        cout << "    - Luong go da dong: " << m3OfWood << " m3" << endl;
        cout << "    - Dien tich kinh da dung: " << m2OfGlass << " m2" << endl;
        cout << "    -> Bao cao thong ke nguyen vat lieu hoan tat!" << endl;
    }
};

// 2. BUILDER INTERFACE (Giao diện builder)
// Cung cấp tất cả bước chung xây dựng nên 1 product

class Builder {
public:
    // loại bỏ sản phẩm cũ trước khi tạo sản phẩm mới
    virtual Builder& Reset() = 0;

    // Các bước xây nhà
    virtual Builder& buildFoundation() = 0; // đổ móng
    virtual Builder& buildWalls() = 0;      // xây tường
    virtual Builder& buildFloor() = 0;      // lát sàn
    virtual Builder& buildRooms() = 0;      // xây phòng
    virtual Builder& buildWindows() = 0;
    virtual Builder& buildRoof() = 0;
    virtual Builder& buildPool() = 0;
    virtual Builder& buildGarden() = 0;
    virtual Builder& buildGarage() = 0;
};

// 3. CONCRETE BUILDER (Các đội thợ cụ thể)

// ĐỘI 1: Đội Thợ Hồ (HouseBuilder) -> Tạo ra House
class HouseBuilder : public Builder {
private:
    string foundationType;
    string wallType;
    string floorType;

    int rooms;
    int windows;

    string roofType;

    bool hasPool;
    bool hasGarden;
    bool hasGarage;

public:
    HouseBuilder() : rooms(0), windows(0), hasPool(false), hasGarden(false), hasGarage(false) {}

    // Reset được dùng khi builder muốn tạo sản phẩm mới
    HouseBuilder& Reset() override {
        foundationType = "";
        wallType = "";
        floorType = "";
        rooms = 0;
        windows = 0;
        roofType = "";
        hasPool = false;
        hasGarden = false;
        hasGarage = false;
        return *this;
    }

    // Implement các hàm build bộ phận
    HouseBuilder& buildFoundation() override {
        foundationType = "don";
        return *this;
    }

    HouseBuilder& buildWalls() override {
        if (foundationType == "") {
            throw logic_error("Nha chua duoc do mong");
        }
        wallType = "gach";
        return *this;
    }

    HouseBuilder& buildFloor() override {
        if (foundationType == "") {
            throw logic_error("Nha chua duoc do mong");
        }
        floorType = "go";
        return *this;
    }

    HouseBuilder& buildRooms() override {
        if (foundationType == "") {
            throw logic_error("Nha chua duoc do mong");
        }
        if (wallType == "") {
            throw logic_error("Nha chua duoc dung tuong");
        }
        rooms = 4;
        return *this;
    }

    HouseBuilder& buildWindows() override {
        if (foundationType == "") {
            throw logic_error("Nha chua duoc do mong");
        }
        if (wallType == "") {
            throw logic_error("Nha chua duoc dung tuong");
        }
        windows = 8;
        return *this;
    }

    HouseBuilder& buildRoof() override {
        if (foundationType == "") {
            throw logic_error("Nha chua duoc do mong");
        }
        if (wallType == "") {
            throw logic_error("Nha chua duoc dung tuong");
        }
        roofType = "ngoi";
        return *this;
    }

    HouseBuilder& buildPool() override {
        hasPool = true;
        return *this;
    }

    HouseBuilder& buildGarden() override {
        hasGarden = true;
        return *this;
    }

    HouseBuilder& buildGarage() override {
        hasGarage = true;
        return *this;
    }

    // Hàm trả hàng riêng của đội thợ hồ: Trả về House
    House build() {
        validate();
        return House(foundationType, wallType, floorType, rooms, windows, roofType, hasPool, hasGarden, hasGarage);
    }

    void validate() {
        if (foundationType == "") {
            throw logic_error("Nha chua duoc do mong");
        }
        if (wallType == "") {
            throw logic_error("Nha chua duoc dung tuong");
        }
        if (floorType == "") {
            throw logic_error("Nha chua duoc lat san");
        }
        if (roofType == "") {
            throw logic_error("Nha chua duoc lop mai");
        }
    }
};

// ĐỘI 2: Đội Dự Toán (EstimatorBuilder) -> Tạo ra ConstructionReport
// Đội này không xây, chỉ đếm số lượng nguyên vật liệu
class EstimatorBuilder : public Builder {
private:
    int tonsOfCement;
    int tonsOfMetal;
    int numBricks;
    int numTiles;
    int m3OfWood;
    int m2OfGlass;

public:
    EstimatorBuilder() : tonsOfCement(0), tonsOfMetal(0), numBricks(0), numTiles(0), m3OfWood(0), m2OfGlass(0) {}

    EstimatorBuilder& Reset() override {
        tonsOfCement = 0;
        tonsOfMetal = 0;
        numBricks = 0;
        numTiles = 0;
        m3OfWood = 0;
        m2OfGlass = 0;
        return *this;
    }

    EstimatorBuilder& buildFoundation() override {
        tonsOfCement += 2;
        tonsOfMetal += 2;
        return *this;
    }

    EstimatorBuilder& buildWalls() override {
        tonsOfCement += 2;
        numBricks += 5000;
        return *this;
    }

    EstimatorBuilder& buildFloor() override {
        tonsOfCement += 2;
        numTiles += 500;
        m3OfWood += 100;
        return *this;
    }

    EstimatorBuilder& buildRooms() override {
        tonsOfCement += 5;
        numBricks += 5000;
        return *this;
    }

    EstimatorBuilder& buildWindows() override {
        tonsOfMetal += 1;
        m2OfGlass += 1000;
        return *this;
    }

    EstimatorBuilder& buildRoof() override {
        numBricks += 1000;
        m3OfWood += 50;
        return *this;
    }

    EstimatorBuilder& buildPool() override {
        numTiles += 500;
        tonsOfCement += 10;
        return *this;
    }

    EstimatorBuilder& buildGarden() override {
        m3OfWood += 10;
        tonsOfMetal += 1;
        return *this;
    }

    EstimatorBuilder& buildGarage() override {
        tonsOfCement += 10;
        tonsOfMetal += 5;
        numBricks += 2000;
        return *this;
    }

    // Hàm trả hàng riêng của đội dự toán: Trả về Construction Report
    ConstructionReport build() {
        return ConstructionReport(tonsOfCement, tonsOfMetal, numBricks, numTiles, m3OfWood, m2OfGlass);
    }
};


// 4. DIRECTOR (Cai thầu / Quản lý dự án)
// Người này nắm quy trình chuẩn để xây một căn biệt thự.
// Không quan tâm đội thợ bên dưới là thợ hồ hay kế toán.

class ConstructionManager {
public:
    void ConstructVilla(Builder& builder) {
        builder.Reset();

        cout << "Cai thau: Bat dau quy trinh xay Biet Thu..." << endl;

        builder.buildFoundation()
               .buildWalls()
               .buildFloor()
               .buildRooms()
               .buildWindows()
               .buildRoof()
               .buildPool()
               .buildGarden()
               .buildGarage();

        cout << "Cai thau: Quy trinh hoan tat. Toi di ve day!" << endl;
    }
};

// 5. CLIENT (Chủ nhà)
int main() {
    // Thuê ông Cai thầu (Director)
    ConstructionManager manager;

    // Xây một căn nhà do ông thầu chỉ đạo
    cout << "KICH BAN A: Muon xay biet thu de o (Thue doi Tho Ho)" << endl;

    try {
        HouseBuilder workerTeam;
        manager.ConstructVilla(workerTeam);
        House myDreamHouse = workerTeam.build();

        myDreamHouse.showHouse();
    }
    catch (const exception& e) {
        cout << "KE HOACH THAT BAI: " << e.what() << endl;
    }

    cout << endl;

    // Lập một bảng báo cáo do cùng một ông thầu đó hướng dẫn, cùng 1 quy trình làm việc
    cout << "KICH BAN B: Muon bao gia du toan (Thue doi Ke toan)" << endl;

    try {
        EstimatorBuilder accountantTeam;
        manager.ConstructVilla(accountantTeam);
        ConstructionReport report = accountantTeam.build();

        report.showReport();
    }
    catch (const exception& e) {
        cout << "KE HOACH THAT BAI: " << e.what() << endl;
    }

    cout << endl;

    // Chủ nhà tự xây nhà mà không cần phải qua tay ông thầu
    cout << "KICH BAN C: Chu nha tu xay nha (Khong thue cai thau)" << endl;
    try {
        HouseBuilder clientBuilder;
        House h = clientBuilder.buildFoundation().buildWalls().buildRoof().buildFloor().build();
        h.showHouse();
    }
    catch (const exception& e) {
        cout << "KE HOACH THAT BAI: " << e.what();
    }

    return 0;
}