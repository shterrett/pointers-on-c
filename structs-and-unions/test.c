typedef struct {
  char name[21];
  char address[41];
  char model[21];
} customer;

typedef struct {
  float msrp;
  float sale_price;
  float sales_tax;
  float lic_fee;
} cash;

typedef struct {
  float msrp;
  float sale_price;
  float down_payment;
  float security_deopsit;
  float monthly_payment;
  int lease_term;
} lease;

typedef struct {
  float msrp;
  float sale_price;
  float sales_tax;
  float lic_fee;
  float down_payment;
  int duration;
  float interest_rate;
  float monthly_payment;
  char name_of_bank[21];
} loan;

enum {
  CASH,
  LEASE,
  LOAN
};

typedef int sale_type;

typedef struct {
  customer cust;
  sale_type typ;
  union {
    cash cash;
    lease lease;
    loan loan;
  } details;
} sale;

////////////////////////////////////////////////////////////////////////////////

typedef struct {
  unsigned dst_reg : 3;
  unsigned dst_mode : 3;
  unsigned opcode : 10;
} sgl_op;

typedef struct {
  unsigned dst_reg : 3;
  unsigned dst_mode : 3;
  unsigned src_reg : 3;
  unsigned src_mode : 3;
  unsigned opcode : 4;
} dbl_op;

typedef struct {
  unsigned offset : 8;
  unsigned opcode : 8;
} branch;

typedef struct {
  unsigned dst_reg : 3;
  unsigned dst_mode : 3;
  unsigned src_reg : 3;
  unsigned opcode : 7;
} reg_src;

typedef struct {
  unsigned opcode : 16;
} misc;

typedef union {
  unsigned short addr;
  misc misc;
  reg_src reg_src;
  branch branch;
  dbl_op dbl_op;
  sgl_op sgl_op;
} machine_inst;

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
  return 0;
}
