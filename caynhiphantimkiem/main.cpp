#include <stdio.h>
#include <iostream>
#include <vector>
#include <istream>
using namespace std;
struct NODE
{
    int data;
    struct NODE *left,*right;
    bool tinhtrangduyet;
    int thutuduyet;
    int solanxuathien;
    struct NODE *Cha;
};
typedef struct NODE node;
void init(node *&root)
{
    root = NULL;
}
node *getnode(int DATA)
{
    node *p=new node;
    
    if(p == NULL)
        return NULL;
    
    p->data = DATA;
    p->left = p->right = NULL;
    p->thutuduyet = 0;
    p->solanxuathien = 1;
    p->Cha = NULL;
    return p;
}
int ThemNodeVaoCay_DeQuy(node *&root, int x,node *k)
{
    if(root != NULL)
    {
        if(x > root->data)
            return ThemNodeVaoCay_DeQuy(root->right, x,root);
        else if(x < root->data)
            return ThemNodeVaoCay_DeQuy(root->left, x,root);
        else
        {
            root->solanxuathien++;
            return 0;
        }
    }
    else
    {
        node *conmoi = getnode(x);
        if(conmoi == NULL)
        {
            return -1;
        }
        
        root = conmoi;
        conmoi->Cha = k;
    }
    return 1;
}
void TaoCay_DeQuy(node *&root , int a[] , int n)
{
    init(root);
    
    for(int i=0; i < n;++i)
    {
        ThemNodeVaoCay_DeQuy(root, a[i],NULL);
    }
}
int ThemNodeVaoCay_KhuDeQuy(node *&root, int x)
{
    if( root == NULL)
    {
        root = getnode(x);
    }
    else{
        node *q = root;
        node *k = q;
        while(q != NULL)
        {
            k = q;
            if( x > q->data)
                q = q->right;
            else if (x < q->data)
                q = q->left;
            else{
                return 0 ;
            }
        }
        node *conmoi = getnode(x);
        
        if(conmoi == NULL)
        {
            cout<<"khong du bo nho";
            return -1;
        }
        
        if(x > k->data)
            k->right = conmoi;
        else if (x < k->data)
            k->left = conmoi;
        
        conmoi->Cha = k;
    }
    return 1;
}
void TaoCay_KhuDeQuy(node *&root , int a[] , int n)
{
    init(root);
    node *goc = root;
    for(int i = 0; i < n;++i)
    {
        //ThemNodeVaoCay_KhuDeQuy(root,goc, a[i]);
        ThemNodeVaoCay_KhuDeQuy(root, a[i]);
    }
}
node *TimNode_DeQuy(node *root, int x,node *truocnode)
{
    if(root == NULL)
       return truocnode;
       
        if(x > root->data)
            return TimNode_DeQuy(root->right, x,root);
        else if(x < root->data)
            return TimNode_DeQuy(root->left, x,root);
        else
        {
            return root;
        }
}
node *TimNode_KhuDeQuy(node *&root, node *goc, int x)
{
    node *p = root;
    node *k = p;
        while(p != NULL)
        {
            k = p;
            if( x > p->data)
               return  p = p->right;
            else if (x < p->data)
                return p = p->left;
            else
            {
                return p;
            }
        }
    return k;
}
void TimPhanTuTheMang_DeQuy(node *&root, node *&p,node *cha = NULL)
{
    if(root->right != NULL){
        TimPhanTuTheMang_DeQuy(root->right, p,root);
    }
    else
    {
        p->data = root->data;
        p = root;
        if(root != NULL && root->left != NULL)
            root->left->Cha = cha;
    }
}
void XoaNode_DeQuy(node *&root, int x,node *dungtruocnode = NULL)
{
    if(dungtruocnode == NULL)
    {
        return ;
    }
    
    if(root != NULL)
    {
        if(x > root->data)
            XoaNode_DeQuy(root->right, x,root);
        else if(x < root->data)
            XoaNode_DeQuy(root->left, x,root);
        else
        {
            node *p = root;
            if(p->left == NULL)
            {
                root = p->right;
                if(p->right != NULL)
                    p->right->Cha = dungtruocnode;
            }
            else if(p->right == NULL)
            {
                root = p->left;
                if(p->left != NULL)
                    p->left->Cha = dungtruocnode;
            }
            else
            {
                TimPhanTuTheMang_DeQuy(root->left, p);
            }
                free(p);
        }
    }
}
void TimPhanTuTheMang_KhuDeQuy(node *&root, node *&q)
{
    node *p = root;
    while (p->right != NULL) {
        p = p->right;
    }
    if(p->Cha->data < p->left->data)
    {
        p->Cha->right = p->left;
    }
    else if(p->Cha->data > p->left->data)
    {
        p->Cha->left = p->left;
    }
    if(p->left != NULL)
    {
        p->left->Cha = p->Cha;
    }
    q->data = p->data;
    q = p;
}
void XoaNode_KhuDeQuy(node *&root, int x)
{
    node *p = root;
    node *k = NULL;
    while(p != NULL)
    {
        if(x > p->data)
        {
            k = p;
            p = p->right;
        }
        else if(x < p->data)
        {
            k = p;
            p = p->left;
        }
        else
        {
            node *q = p;
            if(q->left == NULL)
            {
                if(k != NULL)
                {
                    if(k->data < q->right->data)
                    {
                        k->right = q->right;
                        if(q->right != NULL)
                        {
                            q->right->Cha = k;
                        }
                    }
                    else if(k->data > q->right->data)
                    {
                        k->left = q->right;
                        if(q->right != NULL)
                        {
                            q->right->Cha = k;
                        }
                    }
                }
                else
                {
                    root = root->right;
                    if(root != NULL)
                    {
                        root->Cha = NULL;
                    }
                }
            }
            else if(q->right == NULL)
            {
                if(k != NULL)
                {
                    if(k->data > q->left->data)
                    {
                        k->left = q->left;
                        if(q->left != NULL)
                        {
                            q->left->Cha = k;
                        }
                    }
                    else if(k->data < q->left->data)
                    {
                        k->right = q->left;
                        if(q->left != NULL)
                        {
                            q->left->Cha = k;
                        }
                    }
                }
                else
                {
                    root = root->left;
                    if(root != NULL)
                    {
                        root->Cha = NULL;
                    }
                }
            }
            else
            {
                TimPhanTuTheMang_KhuDeQuy(p->left, q);
            }
            free(q);
            return;
        }
    }
}
void LNR(node *root)
{
    if(root != NULL)
    {
        LNR(root->left);
        cout<< root->data<<" ";
        LNR(root->right);
    }
}
void RNL(node *root)
{
    if(root != NULL)
    {
        LNR(root->right);
        cout<< root->data<<" ";
        LNR(root->left);
    }
}
void giaiphongcay(node *&root)
{
    if(root != NULL)
    {
        giaiphongcay(root->left);
        giaiphongcay(root->right);
        free(root);
        root = NULL;
    }
}
void XoaTatCaCacNodeGiaiPhongCay_DeQuy(node *&Root)
{
    /*while(Root != NULL)
    {
        XoaNodeTrongCay_DeQuy(Root, Root->Data);
    }*/

    if(Root == NULL)
        return;

    XoaNode_DeQuy(Root, Root->data);
    
    XoaTatCaCacNodeGiaiPhongCay_DeQuy(Root);
}
void duyetCayKhongDeQuyKhongStack(node *root)
{
    char s[]="LNR";
    if(root != NULL){
        node *cha = root ->Cha;
        root ->Cha = NULL;
        while (true) {
            if(root->thutuduyet <= 2){
                if(s[root->thutuduyet] == 'N' || s[root->thutuduyet] == 'n')
                {
                    cout << root->data<<" ";
                    root->thutuduyet++;
                }
                else if(s[root->thutuduyet] == 'L' || s[root->thutuduyet] == 'l')
                {
                    root->thutuduyet++;
                    if(root->left != NULL)
                        root=root->left;
                }
                else if(s[root->thutuduyet] == 'R' || s[root->thutuduyet] == 'r')
                {
                    root->thutuduyet++;
                    if(root->right != NULL)
                        root=root->right;
                }
            }
            else
            {
                root->thutuduyet =0;
                if(root->Cha == NULL)
                {
                    root ->Cha= cha;
                    break;
                }
                else{
                    root = root->Cha;
                }
            }
        }
    }
}
// bai tap xu li






node *TimNodeCoGiaTriLonNhat_DeQuy(node *root)
{
   
    if(root == NULL)
        return NULL;
    
    if(root->right != NULL)
    {
        return TimNodeCoGiaTriLonNhat_DeQuy(root->right);
    }
    return root;
}
node *TimNodeCoGiaTriNhoNhat_DeQuy(node *root)
{
   
    if(root == NULL)
        return NULL;
    
    if(root->left != NULL)
    {
        return TimNodeCoGiaTriLonNhat_DeQuy(root->left);
    }
    return root;
}
node* TimNodeCoGiaTriLonNhat_KhuDeQuy(node *root)
{
    if(root == NULL)
        return NULL;
    
    while(root->right != NULL){
            root = root->right;
    }
    
    return root;
}
node* TimNodeCoGiaTriNhoNhat_KhuDeQuy(node *root)
{
    if(root == NULL)
        return NULL;
    
    while (root->left != NULL){
        root = root->left;
    }
    
    return root;
}
void DemCacNodeAm_DeQuy(node *root, int &count)
{
    if(root != NULL)
    {
        DemCacNodeAm_DeQuy(root->left, count);
        if(root->data < 0)
            count++;
        else
        {
            return;
        }
        DemCacNodeAm_DeQuy(root->right, count);
    }
}
void DemNODEAmKhongDeQuyKhongStack(node *root,int &count)
{
    char s[]="LNR";
    if(root != NULL){
        node *cha = root ->Cha;
        root ->Cha = NULL;
        while (true) {
            if(root->thutuduyet <= 2){
                if(s[root->thutuduyet] == 'N' || s[root->thutuduyet] == 'n')
                {
                    if(root->data < 0)
                        count++;
                    else
                    {
                        root->thutuduyet = 0;
                        while(root->Cha != NULL)
                        {
                            root = root->Cha;
                            root->thutuduyet = 0;
                        }
                            root->Cha = cha;
                        break;
                    }
                    root->thutuduyet++;
                }
                else if(s[root->thutuduyet] == 'L' || s[root->thutuduyet] == 'l')
                {
                    root->thutuduyet++;
                    if(root->left != NULL)
                        root=root->left;
                }
                else if(s[root->thutuduyet] == 'R' || s[root->thutuduyet] == 'r')
                {
                    root->thutuduyet++;
                    if(root->right != NULL)
                        root=root->right;
                }
            }
            else
            {
                root->thutuduyet =0;
                if(root->Cha == NULL)
                {
                    root ->Cha= cha;
                    break;
                }
                else{
                    root = root->Cha;
                }
            }
        }
    }
}
void Buoc1_TaoMangChuaCacNodeVaChuaXY_KhuDeQuy(node *root, vector<int> &a, int x, int y)
{
    char s[]="LNR";
    bool check_x = false;
    bool check_y = false;
    if(root != NULL){
        node *cha = root ->Cha;
        root ->Cha = NULL;
        while (true) {
            if(root->thutuduyet <= 2){
                if(s[root->thutuduyet] == 'N' || s[root->thutuduyet] == 'n')
                {
                    if(root->data > x && check_x == false)
                    {
                        a.push_back(x);
                        check_x = true;
                    }
                    if(root->data > y && check_y == false)
                    {
                        a.push_back(y);
                        check_y = true;
                    }
                    a.push_back(root->data);
                    root->thutuduyet++;
                }
                else if(s[root->thutuduyet] == 'L' || s[root->thutuduyet] == 'l')
                {
                    root->thutuduyet++;
                    if(root->left != NULL)
                        root=root->left;
                }
                else if(s[root->thutuduyet] == 'R' || s[root->thutuduyet] == 'r')
                {
                    root->thutuduyet++;
                    if(root->right != NULL)
                        root=root->right;
                }
            }
            else
            {
                root->thutuduyet =0;
                if(root->Cha == NULL)
                {
                    root ->Cha= cha;
                    if(check_x == false)
                        a.push_back(x);
                    if(check_y == false)
                        a.push_back(y);
                    break;
                }
                else{
                    root = root->Cha;
                }
            }
        }
    }
}
long Buoc2_TimKiemNhiPhanPhanTuXY_KhuDeQuy(vector<int> a, int phantutimkiem)
{
    long left = 0;
    long right = a.size()-1;
    
    while(left <= right)
    {
        long mid = (left+right) / 2;
        if(phantutimkiem > a[mid]){
            left = mid + 1;
        }
        else if(phantutimkiem < a[mid])
        {
            right = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}
long DemCacNodeCuaCayNamTrongDoanXY_KhuDeQuy(node *root, int x, int y)
{
    vector<int>arr;
    Buoc1_TaoMangChuaCacNodeVaChuaXY_KhuDeQuy(root, arr, x, y);
    long index_x = Buoc2_TimKiemNhiPhanPhanTuXY_KhuDeQuy(arr, x);
    long index_y = Buoc2_TimKiemNhiPhanPhanTuXY_KhuDeQuy(arr, y);
    if(index_x-1 >= 0 && arr[x] < arr.size()){
        if(arr[index_x -1] == x)
        {
            index_x--;
        }
    }
    if(index_y +1 >=0 && arr[y] < arr.size()){
        if(arr[index_y +1] == y){
            index_y++;
        }
    }
    long ketqua = index_y -index_x + 1 - 2;
    return ketqua;
}
void XuatCacNodeCuaCayNamTrongDoanXY_KhuDeQuy(node *root, int x, int y)
{
    vector<int>arr;
    Buoc1_TaoMangChuaCacNodeVaChuaXY_KhuDeQuy(root, arr, x, y);
    long index_x = Buoc2_TimKiemNhiPhanPhanTuXY_KhuDeQuy(arr, x);
    long index_y = Buoc2_TimKiemNhiPhanPhanTuXY_KhuDeQuy(arr, y);
    if(index_x-1 >= 0 && arr[x] < arr.size()){
        if(arr[index_x -1] == x)
        {
            index_x--;
        }
    }
    if(index_y +1 >=0 && arr[y] < arr.size()){
        if(arr[index_y +1] == y){
            index_y++;
        }
    }
    for(long i = index_x + 1 ; i < index_y; ++i)
    {
        cout<<arr[i]<<" ";
    }
}
void KiemTraCayNhiPhanCoLaCayNhiPhanTimKiem_DeQuy(node *root, int &temp, bool &KiemTra)
{
    if(root != NULL)
    {
        KiemTraCayNhiPhanCoLaCayNhiPhanTimKiem_DeQuy(root->left, temp, KiemTra);
        if(root->data > temp && KiemTra == true)
        {
            temp = root->data;
        }
        else {
            KiemTra = false;
            return ;
        }
        KiemTraCayNhiPhanCoLaCayNhiPhanTimKiem_DeQuy(root->right, temp, KiemTra);
    }
}
bool KiemTraCayNhiPhanCoLaCayNhiPhanTimKiem_KhuDeQuy(node *root)
{
    char s[]="LNR";
    int temp = INT8_MIN;
    if(root != NULL){
        node *cha = root ->Cha;
        root ->Cha = NULL;
        while (true) {
            if(root->thutuduyet <= 2){
                if(s[root->thutuduyet] == 'N' || s[root->thutuduyet] == 'n')
                {
                    if(root->data > temp)
                    {
                        temp = root->data;
                    }
                    else {
                        root->thutuduyet = 0;
                        while(root->Cha != NULL)
                        {
                            root = root->Cha;
                            root->thutuduyet = 0;
                        }
                        return false;
                    }
                    root->thutuduyet++;
                }
                else if(s[root->thutuduyet] == 'L' || s[root->thutuduyet] == 'l')
                {
                    root->thutuduyet++;
                    if(root->left != NULL)
                        root=root->left;
                }
                else if(s[root->thutuduyet] == 'R' || s[root->thutuduyet] == 'r')
                {
                    root->thutuduyet++;
                    if(root->right != NULL)
                        root=root->right;
                }
            }
            else
            {
                root->thutuduyet =0;
                if(root->Cha == NULL)
                {
                    root ->Cha= cha;
                    break;
                }
                else{
                    root = root->Cha;
                }
            }
        }
    }
    return true;
}
void DemSoLuongGiaTriPhanBietVaTanSuatXuatHien_DeQuy(node *root, int &count)
{
    if(root != NULL)
    {
        cout<<"\ngia tri "<<root->data<<" xuat hien "<< root->solanxuathien<<" lan";
        count++;
        DemSoLuongGiaTriPhanBietVaTanSuatXuatHien_DeQuy(root->left, count);
        DemSoLuongGiaTriPhanBietVaTanSuatXuatHien_DeQuy(root->right, count);
    }
}
void DemSoLuongGiaTriPhanBietVaTanSuatXuatHien_KhuDeQuy(node *root)
{
    char s[]="LNR";
    int count = 0;
    if(root != NULL){
        node *cha = root ->Cha;
        root ->Cha = NULL;
        while (true) {
            if(root->thutuduyet <= 2){
                if(s[root->thutuduyet] == 'N' || s[root->thutuduyet] == 'n')
                {
                    cout<<"\ngia tri "<<root->data<<" xuat hien "<<root->solanxuathien<<" lan";
                    count++;
                    root->thutuduyet++;
                }
                else if(s[root->thutuduyet] == 'L' || s[root->thutuduyet] == 'l')
                {
                    root->thutuduyet++;
                    if(root->left != NULL)
                        root=root->left;
                }
                else if(s[root->thutuduyet] == 'R' || s[root->thutuduyet] == 'r')
                {
                    root->thutuduyet++;
                    if(root->right != NULL)
                        root=root->right;
                }
            }
            else
            {
                root->thutuduyet =0;
                if(root->Cha == NULL)
                {
                    root ->Cha= cha;
                    break;
                }
                else{
                    root = root->Cha;
                }
            }
        }
    }
}
void TaoCayNhapTuBanPhimBietTruocSoLuong(node *&root, int &n)
{
    init(root);
    do{
        printf("\nNhap vao so luong Node cua cay: ");
        scanf("%d", &n);

        if(n < 0)
            printf("\nSo luong phai la so duong. Xin kiem tra lai!");
    }while(n < 0);
    for(int i = 1; i <= n;++i)
    {
        int x;
        cin>>x;
        ThemNodeVaoCay_DeQuy(root, x, NULL);
    }
}
void TaoCayNhapTuBanPhimKhongBietTruocSoLuong(node *&root, int &n)
{
    init(root);
    int i = 1;
    while(true)
    {
        int x;
        printf("\nNhap vao gia tri cua Node thu %d (Nhap so 123456 de ket thuc): ", i);
        cin>>x;
        if(x == 111)
        {
            cout<<"\nGia tri 123456 Ban vua nhap la de ket thuc hay muon tao ra 1 Node moi co gia tri la 123456? Neu de ket thuc thi nhan phim Y, neu khong muon ket thuc thi nhan phim N";
            char c = getchar();
            if(c == 'y' || c == 'Y')
                break;
        }
        ThemNodeVaoCay_DeQuy(root, x, NULL);
        int ketqua = ThemNodeVaoCay_KhuDeQuy(root, x);
        if(ketqua == 1)
        {
            i++;
        }
        else if(ketqua == -1)
        {
            cout<<"het bo nho khong the tao";
        }
        else if(ketqua == 0)
        {
            printf("\nLoi: Gia tri Node nay da co ton tai trong cay roi cho nen khong them vao cay duoc nua");
        }
    }
}
void TaoCayTuTapTin(node *&root, FILE *FileIn)
{
    //INit(Root); // Phải nhớ khởi tạo cho cây để tránh bị lỗi

    // Trường hợp dòng đầu tiên trong file tượng trưng cho số lượng data
    //int n;
    //fscanf(FileIn, "%d", &n);

    //for(int i = 1; i <= n; ++i)

    // Trường hợp không biết trước số lượng có bao nhiêu dòng data trong file => cứ đọc hết từ đầu đến cuối
    while(!feof(FileIn))
    {
        int x;
        if(fscanf(FileIn, "%d",&x) == 1)
            ThemNodeVaoCay_KhuDeQuy(root, x);
    }
}
/*int main()
{
    node *root;
    int a[]={-22,-33,5,-1,-3,21,21,8,15};
    int n = sizeof(a)/sizeof(a[0]);
    TaoCay_DeQuy(root, a, n);
    //TaoCay_KhuDeQuy(root, a, n);
    cout<<"LNR : ";
    LNR(root);
    // int c =8;
    //node *p=TimNode_KhuDeQuy(root, root, 4);
    if(p == NULL)
     {
     cout <<"\nkhong tim thay\n";
     }
     else
     {
     cout <<"\ntim thay phan tu\n";
     }
    //cout<<n;
    //cout<<"\nxoa node 8 : ";
    //XoaNode_DeQuy(root, 15);
    //node *goc = root;
    //ThemNodeVaoCay_KhuDeQuy(root, goc, 22);
    //XoaNode_KhuDeQuy(root, 2);
    //LNR(root);
    //duyetCayKhongDeQuyKhongStack(root);
    //giaiphongcay(root);
    int x = 0;
    int y = 9;
    cout <<"\n";
    vector<int>c;
    Buoc1_TaoMangChuaCacNodeVaChuaXY_KhuDeQuy(root, c, x, y);
    for(int i = 0; i < c.size(); ++i)
    {
        cout<<c[i]<<" ";
    }
    cout<<"\n";
    XuatCacNodeCuaCayNamTrongDoanXY_KhuDeQuy(root, x, y);
    int count = 0;
    DemSoLuongGiaTriPhanBietVaTanSuatXuatHien_KhuDeQuy(root);
    
    system("pause");
    return 0;
}*/
int main()
{
    node *root;
    init(root);
    int menu1;
    do {
        printf("\n===============> Menu <===============\n");
        printf("\n1. Doc du lieu tu tap tin vao cay");
        printf("\n2. Them Node vao cay (du lieu nhap vao tu ban phim)");
        printf("\n3. Tim kiem Node");
        printf("\n4. Xoa Node");
        printf("\n5. Duyet cay");
        printf("\n6. Giai phong cay");
        printf("\n7. Cac bai tap xu ly cay");
        printf("\n0. Thoat chuong trinh");
        printf("\n======================================\n");

        printf("\nNhap vao lua chon (0 -> 7): ");
        scanf("%d", &menu1);
        if(menu1 < 0 || menu1 > 7)
        {
            cout<<"\nLua chon chi duoc trong khoang 0 -> 7. Nhan enter nhap lai!";
            //system("pause");
            //system("cls");
        }
    } while (menu1 < 0 || menu1 > 7);
    cout<<"abc";
    system("pause");
    return 0;
}

