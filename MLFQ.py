class Job:
    def __init__(self, name, cpu_cycles, arrival_time, io_time=None, io_duration=0):
        self.name = name
        self.cpu_cycles = cpu_cycles
        self.arrival_time = arrival_time
        self.current_queue = 3  # 모든 작업은 Q3에서 시작
        self.remaining_time_in_queue = 6  # 초기 배정 시간, AL
        self.io_time = io_time
        self.io_duration = io_duration
        self.finished_time = None
        self.time_spent = 0  # 현재까지 CPU에서 실행한 시간
        self.is_blocked = False

    def execute(self, current_time):
        if self.is_blocked:
            # IO 대기 상태일 때, IO 완료 시간이 도래하면 작업을 재개합니다.
            if current_time >= self.io_time + self.io_duration:
                self.is_blocked = False
                self.io_time = None
                print(f"{current_time}: {self.name} resumes in queue Q{self.current_queue}")
        elif self.cpu_cycles > 0:
            self.cpu_cycles -= 1
            self.time_spent += 1
            self.remaining_time_in_queue -= 1
            print(f"{current_time}: {self.name} running in queue Q{self.current_queue}")

            # IO 시작 검사
            if self.io_time is not None and self.io_time == current_time:
                self.is_blocked = True
                print(f"{current_time}: {self.name} starts I/O")
                return

            # 현재 큐에서의 시간이 끝나면 다음 큐로 이동
            if self.remaining_time_in_queue == 0:
                if self.current_queue > 1:
                    self.current_queue -= 1
                    self.remaining_time_in_queue = 6  # 다음 큐에서의 새 배정 시간
                    print(f"{current_time}: {self.name} moves to queue Q{self.current_queue}")
                else:
                    # Q1에서 더 이상 내려갈 수 없으므로 계속 Q1에 머무르게 됩니다.
                    self.remaining_time_in_queue = 6

            if self.cpu_cycles == 0:
                self.finished_time = current_time
                print(f"{current_time}: {self.name} finished at queue Q{self.current_queue}")

def simulate_mlfq():
    # 초기 작업 설정
    jobs = [
        Job("Job A", 90, 2), # 작업명, burst time, arrival time, 
        Job("Job B", 5, 0, io_time=5, io_duration=7),
        Job("Job C", 5, 4, io_time=9, io_duration=5)
    ]

    current_time = 0
    while any(job.cpu_cycles > 0 for job in jobs):
        for job in jobs:
            if job.arrival_time <= current_time and job.cpu_cycles > 0 and not job.is_blocked:
                job.execute(current_time)
        current_time += 1

    # 출력
    for job in jobs:
        print(f"{job.name} finished at time {job.finished_time}, in queue Q{job.current_queue}")

simulate_mlfq()
