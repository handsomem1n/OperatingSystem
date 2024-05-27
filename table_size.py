# 계산할 값들을 설정
virtual_address_bits = 24
page_size_kb = 1  # KB
pte_size_bytes = 2  # bytes

# 전체 페이지 수 계산
total_pages = (2 ** virtual_address_bits) / (page_size_kb * 1024)

# 페이지 테이블의 크기 계산
page_table_size_bytes = total_pages * pte_size_bytes
page_table_size_bytes, page_table_size_bytes / 1024  # 바이트와 킬로바이트 단위 결과
